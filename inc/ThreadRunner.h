// David Sami 2015

#ifndef THREADRUNNER_H
#define THREADRUNNER_H

#include <memory>
#include "Scene.h"
#include "Shader.h"
#include "ThreadPool.h"

class ThreadRunner {
public:
    ThreadRunner(ThreadPool* aPool, std::shared_ptr<const Scene> aScene, std::shared_ptr<Shader> aShader);
    void Run();
private:
    ThreadPool* mPool;
    std::shared_ptr<const Scene> mScene;
    std::shared_ptr<Shader> mShader;
};

#endif
