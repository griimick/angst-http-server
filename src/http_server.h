// Defines the HTTP server object with some constants and structs
// useful for request handling and improving performance

#ifndef ANGST_HTTP_SERVER_H_
#define ANGST_HTTP_SERVER_H_

#include <sys/epoll.h>
#include <sys/socket.h>
#include <sys/types.h>

#include <chrono>
#include <functional>  // std::function
#include <map>         // std::map
#include <string>      // std::string
#include <thread>      // std::thread
#include <utility>     // std::function, std::make_pair

#include "http_msg.h"
#include "uri.h"

namespace angst_http_server {

	// Maximum size of an HTTP message is limited by how much bytes
	// we can read or send via socket each time
	constexpr size_t kMaxBufferSize = 4096;

	struct EventData {
		EventData() : fd(0), length(0), cursor(0), buffer() {}
		int fd;
		size_t length;
		size_t cursor;
		char buffer[kMaxBufferSize];
	};

	// A request handler should expect a request as argument and returns a response
	using HttpRequestHandler_t = std::function<HttpResponse(const HttpRequest&)>;

	class HttpServer {
		public:
			explicit HttpServer(const std::string& host, std::uint16_t port);
			~HttpServer() = default;

			HttpServer() = default;
			HttpServer(HttpServer&&) = default;             /* copy constructor using C++ 11 rvalue reference */
			HttpServer& operator=(HttpServer&&) = default;

			void Start();
			void Stop();

			/* Register a handler for a given path and HTTP method */
			void RegisterHttpRequestHandler(const std::string& path, HttpMethod method,
					const HttpRequestHandler_t callback) {
				Uri uri(path);
				request_handlers_[uri].insert(std::make_pair(method, std::move(callback)));
			}

			/* Register a handler for a given URI and  HTTP methods */
			void RegisterHttpRequestHandler(const Uri& uri, HttpMethod method,
					const HttpRequestHandler_t callback) {
				request_handlers_[uri].insert(std::make_pair(method, std::move(callback)));
			}

			std::string host() const { return host_; }
			std::uint16_t port() const { return port_; }
			bool running() const { return running_; }

		private:
			static constexpr int kBacklogSize = 1000;
			static constexpr int kMaxConnections = 10000;
			static constexpr int kMaxEvents = 10000;
			static constexpr int kThreadPoolSize = 5;

			std::string host_;                                       /* hostname                                           */
			std::uint16_t port_;                                     /* port to listen on                                  */
			int sock_fd_;                                            /* socket file descriptor                             */
			bool running_;                                           /* true if the server is running                      */
			std::thread listener_thread_;                            /* 1 listener thread listening for new connections    */
			std::thread worker_threads_[kThreadPoolSize];            /* kThreadPoolSize worker threads processing requests */
			int worker_epoll_fd_[kThreadPoolSize];                   /* kThreadPoolSize epoll fds for worker threads       */
			epoll_event worker_events_[kThreadPoolSize][kMaxEvents]; /* kThreadPoolSize epoll events for worker threads    */
			std::map<Uri, std::map<HttpMethod, HttpRequestHandler_t>> request_handlers_;

			void CreateSocket();
			void SetUpEpoll();
			void Listen();
			void ProcessEvents(int worker_id);
			void HandleEpollEvent(int epoll_fd, EventData* event, std::uint32_t events);
			void HandleHttpData(const EventData& request, EventData* response);
			HttpResponse HandleHttpRequest(const HttpRequest& request);

			void control_epoll_event(int epoll_fd, int op, int fd,
					std::uint32_t events = 0, void* data = nullptr);
	};

}  // namespace angst_http_server

#endif  // ANGST_HTTP_SERVER_H_
