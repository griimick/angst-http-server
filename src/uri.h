/* URI definitions (Uniform Resource Identifier */
#ifndef ANGST_URI_H
#define ANGST_URI_H

#include <algorithm> // std::transform
#include <string>    // std::string
#include <utility>   // std::move, std::unint16_t

namespace angst_http_server {

	// A Uri object will contain a valid scheme (for example: HTTP), host,
	// port, and the actual URI path
	class Uri {

		public:
			Uri() = default; /* Use compiler-generated default constructor */
			/* Do not allow implicit conversion from string to Uri */
			explicit Uri(const std::string& path) : path_(path) { SetPathToLowercase(); } 
			~Uri() = default; /* Use compiler-generated default destructor */

			inline bool operator<(const Uri& other) const { return path_ < other.path_; }
			inline bool operator==(const Uri& other) const {
				return path_ == other.path_;
			}

			void SetPath(const std::string& path) {
				path_ = std::move(path);
				SetPathToLowercase();
			}

			std::string scheme() const { return scheme_; }
			std::string host() const { return host_; }
			std::uint16_t port() const { return port_; } /* max port is 65535 16bit */
			std::string path() const { return path_; }

		private:
			std::string path_;
			std::string scheme_; /* TODO: unsupported */
			std::string host_;   /* TODO: unsupported */
			std::uint16_t port_; /* TODO: unsupported */

			void SetPathToLowercase() {
				std::transform(path_.begin(), path_.end(), path_.begin(),
						[](char& c) { return tolower(c); });
			}
	};

}  // namespace angst_http_server

#endif  // ANGST_URI_H
