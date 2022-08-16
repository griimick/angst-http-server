# angst-http-server

I did this to study multithreading and socket programming in cpp. Also a way to avoid things I should focus on irl :)
Hopefully, I would be able to write up my learning from this in my non existent blog.

## Features
- [x] Accept connections
- [x] Parse incoming HTTP request messages
- [x] Handle GET and HEAD HTTP methods
- [x] Ability to send Response header and payload
- [x] Concurrent request handling using worker threads. 

## Known issues
- [ ] Only support HTTP 1.1
- [ ] HTTP request and URI parsing is purely experiemental

## Learnings

1. C++11 specifics
    1. [default constructor](https://en.cppreference.com/w/cpp/language/default_constructor)
    2. [move constructor and semantics](https://en.cppreference.com/w/cpp/language/move_constructor)
    3. [copy constructor](https://en.cppreference.com/w/cpp/language/copy_constructor)
    4. [explicit keyword](https://en.cppreference.com/w/cpp/language/explicit)
    5. [constexpr keyword](https://en.cppreference.com/w/cpp/language/constexpr)
    6. [function wrapper](https://en.cppreference.com/w/cpp/utility/functional/function)
    7. [error types](https://en.cppreference.com/w/cpp/error)
    8. [Rvalue references (&&)](https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2006/n2027.html#Move_Semantics)
2. CMake, Make and build systems 
	1. http://derekmolloy.ie/hello-world-introductions-to-cmake/
3. linux specifics
	1. [epoll](https://jvns.ca/blog/2017/06/03/async-io-on-linux--select--poll--and-epoll/)
	2. [file descriptor](https://bottomupcs.com/ch01s03.html)
	3. [socket](https://man7.org/linux/man-pages/man2/socket.2.html)
	4. listener and worker threads
4. HTTP and REST
	1. [HEAD method](https://developer.mozilla.org/en-US/docs/Web/HTTP/Methods/HEAD)
	2. HTTP request and response structure


## References

- [Beej's Guide to Network Programming](https://beej.us/guide/bgnet/html/#client-server-background)
- [A simple HTTP server from scratch](https://trungams.github.io/2020-08-23-a-simple-http-server-from-scratch/)
- [Concurrent HTTP Server with Epoll](https://kaleid-liner.github.io/blog/2019/06/02/epoll-web-server.html)
- [The Little Book of Semaphores – Green Tea Press](https://greenteapress.com/wp/semaphores/)
- [Node's Event Loop From the Inside Out by Sam Roberts, IBM](https://www.youtube.com/watch?v=P9csgxBgaZ8)
