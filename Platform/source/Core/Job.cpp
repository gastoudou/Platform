#include "Core/stdafx.h"
#include "Job.h"

template <typename T, size_t capacity>
class ThreadSafeRingBuffer
{
public:
	inline bool push_back( const T& item )
	{
		bool result = false;
		lock.lock();
		size_t next = ( head + 1 ) % capacity;
		if ( next != tail )
		{
			data[ head ] = item;
			head = next;
			result = true;
		}
		lock.unlock();
		return result;
	}

	inline bool pop_front( T& item )
	{
		bool result = false;
		lock.lock();
		if ( tail != head )
		{
			item = data[ tail ];
			tail = ( tail + 1 ) % capacity;
			result = true;
		}
		lock.unlock();
		return result;
	}

private:
	T data[ capacity ];
	size_t head = 0u;
	size_t tail = 0u;
	std::mutex lock;
};

namespace JobSystem
{
	uint32_t numThreads = 0u;
	ThreadSafeRingBuffer<std::function<void()>, 256u> jobPool;
	std::condition_variable wakeCondition;
	std::mutex wakeMutex;
	uint64_t currentLabel = 0u;
	std::atomic<uint64_t> finishedLabel;

	void Initialize()
	{
		finishedLabel.store( 0u );

		auto numCores = std::thread::hardware_concurrency() - 1u;
		numThreads = std::max( 1u, numCores );

		for ( uint32_t threadID = 0; threadID < numThreads; ++threadID )
		{
			std::thread worker( []
				{
					std::function<void()> job;

					while ( true )
					{
						if ( jobPool.pop_front( job ) )
						{
							job();
							finishedLabel.fetch_add( 1 );
						}
						else
						{
							std::unique_lock<std::mutex> lock( wakeMutex );
							wakeCondition.wait( lock );
						}
					}
				} );

			worker.detach();
		}
	}

	inline void poll()
	{
		wakeCondition.notify_one();
		std::this_thread::yield();
	}

	void Execute( const std::function<void()>& job )
	{
		currentLabel += 1;
		while ( !jobPool.push_back( job ) )
		{
			poll();
		}
		wakeCondition.notify_one();
	}

	bool IsBusy()
	{
		return finishedLabel.load() < currentLabel;
	}

	void Wait()
	{
		while ( IsBusy() )
		{
			poll();
		}
	}

	void Dispatch( uint32_t jobCount, uint32_t groupSize, const std::function<void( JobDispatchArgs )>& job )
	{
		if ( jobCount == 0u || groupSize == 0u )
		{
			return;
		}

		const uint32_t groupCount = ( jobCount + groupSize - 1 ) / groupSize;

		currentLabel += groupCount;

		for ( uint32_t groupIndex = 0; groupIndex < groupCount; ++groupIndex )
		{
			auto jobGroup = [ jobCount, groupSize, job, groupIndex ] ()
			{
				const uint32_t groupJobOffset = groupIndex * groupSize;
				const uint32_t groupJobEnd = std::min( groupJobOffset + groupSize, jobCount );

				JobDispatchArgs args;
				args.groupIndex = groupIndex;

				for ( uint32_t i = groupJobOffset; i < groupJobEnd; ++i )
				{
					args.jobIndex = i;
					job( args );
				}
			};

			while ( !jobPool.push_back( jobGroup ) )
			{
				poll();
			}

			wakeCondition.notify_one();
		}
	}
}