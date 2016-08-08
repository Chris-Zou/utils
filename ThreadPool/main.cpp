//
//  main.cpp
//  cpp11
//
//  Created by Chriszou on 8/6/16.
//  Copyright © 2016 Chriszou. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
#include <future>
#include <thread>
#include <chrono>

#include "ThreadPool.h"

int main(int argc, const char * argv[]) {
    
    ThreadPool pool(4);
    std::vector<std::future<std::string> > results;
    for(int i = 0; i < 8; i ++){
        results.emplace_back(
            pool.enqueue([i]{
            std::cout << "hello " << i;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            std::cout << "world!" << std::endl;
            return std::string("---thread ") + std::to_string(i) + std::string(" finished.---");
        })
        );
    }
    
    for(auto && result : results){
        std::cout << result.get() << ' ';
    }
    
    std::cout << std::endl;
    
    return 0;
}
