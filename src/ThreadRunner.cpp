// David Sami 2015

#include "ThreadRunner.h"

ThreadRunner::ThreadRunner(ThreadPool* aPool, std::shared_ptr<const Scene> aScene, std::shared_ptr<Shader> aShader):
    mPool(aPool), mScene(aScene), mShader(aShader)
{
}

void ThreadRunner::Run(){
    // Check only once per pixel whether to continue running
    while(mPool->ContinueRunning()){
        ThreadWork work;

        if(mPool->GetWork(&work)){
            *work.mPixel = mShader->CastRay(work.mRay, *mScene);
        }
    }
}
