#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <curl/curl.h>
#include <cstdlib>
using namespace std;

class Request {

private:
	string URL;
	string content_buffer;
	string header_buffer;
	curl_slist* header_list;

	static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp)
	{
		((std::string*)userp)->append((char*)contents, size * nmemb);
		return size * nmemb;
	}
	void authenticate(CURL* curl, const char* user, const char* password) {
		curl_easy_setopt(curl, CURLOPT_USERNAME, user);
		curl_easy_setopt(curl, CURLOPT_PASSWORD, password);
	}

public:
	Request() {
		URL = "";
		content_buffer = "";
		header_buffer = "";
		header_list = NULL;
	};
	Request(string URL) {
		this->URL = URL;
		content_buffer = "";
		header_buffer = "";
		header_list = NULL;
	}
	Request(string URL,	string& content_buffer) {
		this->URL = URL;
		this->content_buffer = content_buffer;
		header_buffer = "";
		header_list = NULL;
	}
	Request(string URL, string& content_buffer, string& header_buffer, curl_slist* header_list) {
		this->URL = URL;
		this->content_buffer = content_buffer;
		this->header_buffer = header_buffer;
		this->header_list = header_list;
	};
	
	void setURL(string URL) {this->URL = URL;}
	void setContentBuffer(string &buff) { this->content_buffer = buff; }
	void setHeaderBuffer(string &buff) { this->header_buffer = buff; }

	string getURL() { return URL; }
	string getContentBuffer() { return content_buffer; }
	string getHeaderBuffer() { return header_buffer; }
	curl_slist* getHeaderList() { return header_list; }

	void print() {

		std::cout << header_buffer << std::endl;
		std::cout << content_buffer << std::endl;
	}

	void addHeader(string header) {
		this->header_list = curl_slist_append(this->header_list, header.c_str());
	};
	
	CURLcode curl(const char* user, const char* password, string post_fields) {
		CURL* curl;
		CURLcode result;

		curl = curl_easy_init();

		if (curl) {
			curl_easy_setopt(curl, CURLOPT_URL, URL.c_str());
			authenticate(curl, user, password);
			curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header_list);
			curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_fields.c_str());
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
			curl_easy_setopt(curl, CURLOPT_HEADERDATA, &header_buffer);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, &content_buffer);

			result = curl_easy_perform(curl);
			curl_easy_cleanup(curl);

		}
		else {
			exception("Could not curl", -1);
		}

		return result;

	}
	CURLcode curl(const char* user, const char* password) {
		CURL* curl;
		CURLcode result;

		curl = curl_easy_init();

		if (curl) {
			curl_easy_setopt(curl, CURLOPT_URL, URL.c_str());
			authenticate(curl, user, password);
			curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header_list);
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
			curl_easy_setopt(curl, CURLOPT_HEADERDATA, &header_buffer);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, &content_buffer);

			result = curl_easy_perform(curl);
			curl_easy_cleanup(curl);

		}
		else {
			exception("Could not curl", -1);
		}

		return result;

	}

	
	

};
