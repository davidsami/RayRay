// David Sami 2015

#include "ThreadPool.h"
#include "ThreadRunner.h"

static void run_thread(ThreadPool* aPool,
        std::shared_ptr<const Scene> aScene,
        std::shared_ptr<Shader> aShader)
{
    ThreadRunner runner(aPool, aScene, aShader);

    runner.Run();
}

ThreadPool::ThreadPool():mContinue(true) {}

void ThreadPool::Init(int aNumThreads,
    std::shared_ptr<const Scene> aScene,
    std::shared_ptr<Shader> aShader)
{
    for(int i = 0; i < aNumThreads; i++){
        mThreads.push_back(std::thread(run_thread, this, aScene, aShader));
    }
}

void ThreadPool::AddWork(ThreadWork& aWork){
    std::lock_guard<std::mutex> lock(mMutex);

    mQueue.push(aWork);
}

bool ThreadPool::GetWork(ThreadWork* aWork){
    std::lock_guard<std::mutex> lock(mMutex);

    bool ret = !mQueue.empty();
    if(ret){
        *aWork = mQueue.front();
        mQueue.pop();
    }

    return ret;
}

bool ThreadPool::ContinueRunning(){
    return mContinue;
}

void ThreadPool::StopThreads(){
    mContinue = false;
    for(auto it = mThreads.begin(); it != mThreads.end(); it++){
        it->join();
    }
}

bool ThreadPool::WorkLeft(){
    return !mQueue.empty();
}
