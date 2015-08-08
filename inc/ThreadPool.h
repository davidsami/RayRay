// David Sami 2015

#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <memory>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>
#include "Math.h"
#include "Scene.h"
#include "Shader.h"

struct ThreadWork{
    // Input
    Math::Ray mRay;

    // Output
    Colour* mPixel;
};

class ThreadPool {
public:
    ThreadPool();
    void Init(int aNumThreads,
        std::shared_ptr<const Scene> aScene,
        std::shared_ptr<Shader> aShader);

    // To be called from RayRay
    void AddWork(ThreadWork& aWork);
    void StopThreads();
    bool WorkLeft();

    // To be called from ThreadRunner
    bool GetWork(ThreadWork* aWork);
    bool ContinueRunning();
private:
    std::queue<ThreadWork> mQueue;
    std::mutex mMutex;
    std::vector<std::thread> mThreads;
    bool mContinue;
};

#endif
