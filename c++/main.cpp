#include <mutex>
#include <thread>
#include <iostream>
#include "prefix_tree.hpp"
#include <vector>
#include <cassert>
int main() {
    mutex mtx;

    // unit test 1
    vector<string> arr;
    arr.push_back("youtube/a/b/c");
    arr.push_back("youtube/a/d/c");
    arr.push_back("youtube/a/e/c");
    arr.push_back("youtube/a/q/c");
    arr.push_back("youtube/a/p/c");
    arr.push_back("youtube/a/w/c");
    arr.push_back("youtube/a/v/c");
    arr.push_back("youtube/a/h/c");
    arr.push_back("youtube/a/m/c");
    arr.push_back("youtube/a/c");
    tree::prefix_tree *pt_root = new tree::prefix_tree(arr);
    auto func = [&]() {

        pt_root->constructTrie();
        string rc = pt_root->walkTrie();
       assert(rc.compare("youtube/a/") == 0);
        assert(pt_root->search("youtube") == true);
         delete pt_root;
        pt_root = NULL;
        mtx.lock();
        cout << "test1 passed" << endl;
        mtx.unlock();


    };

    //unit test 2
    vector<string> arr2;
    arr2.push_back("youtube/a/b/c");
    arr2.push_back("youtube/a/b/d");
    arr2.push_back("youtube/a/b/e");
    arr2.push_back("youtube/a/b/f");
    arr2.push_back("youtube/a/b/g");
    arr2.push_back("youtube/a/b/h");
    arr2.push_back("youtube/a/b/i");
    arr2.push_back("youtube/a/b/j");
    arr2.push_back("youtube/a/b/k");
    tree::prefix_tree *pt_root1 = new tree::prefix_tree(arr2);

    // multiple thread testing
    auto func2 = [&]() {

        pt_root1->constructTrie();
        string rc1 = pt_root1->walkTrie();
        assert(rc1.compare("youtube/a/b/") == 0);
        delete pt_root1;
        pt_root1 = NULL;
        mtx.lock();
        cout << "test2 passed" << endl;
        mtx.unlock();
        // cout << "test2 passed" << endl;
    };

    thread th(func);
    thread th1(func2);
    th.join();
    th1.join();
  //  mtx.lock();
    cout << "here we are" << endl;
    //mtx.unlock();
}
