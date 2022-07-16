#include "pch.h"
#include "CppUnitTest.h"
#include "../quickbase3/Request.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestsForQuickbaseCraftDemo
{
	TEST_CLASS(UnitTestsForQuickbaseCraftDemo)
	{
	public:
		
		TEST_METHOD(requestInitTest)
		{
			std::string url = "URL";
			Request req(url);
			Assert::AreEqual(url, req.getURL());
		}

		TEST_METHOD(requestInitTest2)
		{
			std::string url = "URL";
			string content_buffer = "Buffer";
			
			Request req(url, content_buffer);
			Assert::AreEqual(url, req.getURL());
			Assert::AreEqual(content_buffer, req.getContentBuffer());
		}

		TEST_METHOD(requestInitTest3)
		{
			std::string url = "URL";
			string content_buffer = "Buffer";
			string header_buffer = "HeaderBuff";
			curl_slist* header_list = NULL;

			Request req(url, content_buffer, header_buffer, header_list);
			Assert::AreEqual(url, req.getURL());
			Assert::AreEqual(content_buffer, req.getContentBuffer());
			Assert::AreEqual(header_buffer, req.getHeaderBuffer());
			Assert::IsNull(req.getHeaderList());

		}

		TEST_METHOD(addHeaderTest)
		{
			std::string header = "header";
			Request req(header);
			req.addHeader(header);
			Assert::IsNotNull(req.getHeaderList());
		}
	};
}
