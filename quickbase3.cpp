#define _CRT_SECURE_NO_WARNINGS
#include "Request.h"
using namespace std;

//finds the fields and their value in the json buffer
string extract_contact(vector<string> fields,const string& buffer) {
	string contact = "";
	//for each of the categories extract the information
	for (size_t i = 0; i < fields.size(); i++)
	{
		size_t idx = buffer.find(fields[i], 0);
		if (idx == std::string::npos) {
			continue;
		}

		int k = fields[i].size();
		string info_content = "";

		while (buffer[idx + k + 2] != ',') {
			info_content += buffer[idx + k + 2];
			k++;
		} //ex.  "email":null The +2 is for ":

		if (info_content == "null") {
			continue;
		}
		else if (fields[i] == "id") {
			contact += "\"unique_external_id\": \"" + info_content + "\"" + ", ";
		}
		else if (info_content[0] == '"') {
			contact += "\"" + fields[i] + "\": " + info_content + ", ";
		}
		else contact += "\"" + fields[i] + "\": " + "\"" + info_content + "\"" + ", ";
		cout << fields[i] << ": " << info_content << endl;

	}

	string contact_str = "{" + contact.substr(0, contact.length() - 2) + " }"; //-2 to remove the additional ", "
	return contact_str;
}


int main(int argc, char* argv[])
{
	//fields to look for in github profile
	vector<string> field_info = { "name", "id", "email", "location" };

	//github info for curl
	//string username = "AvaHadassah";
	string username = argv[1];
	
	std::string gh_user_buffer;
	string username_url = "https://api.github.com/users/" + username;
	string useragent = "User-Agent: " + username;
	
	Request github(username_url, gh_user_buffer);
	github.addHeader(useragent);
	github.curl(username.c_str(), getenv("GITHUB_TOKEN"));
	github.print();


	//freshdesk info for curl
	std::string fr_buffer;

	//string freshdesk_url = "https://ava-assist.freshdesk.com/api/v2/contacts";
	string subdomain = argv[2];
	string freshdesk_url = "https://" + subdomain + ".freshdesk.com/api/v2/contacts";

	string contact_str = extract_contact(field_info, github.getContentBuffer());
	cout <<"\n\n\n"<< contact_str << endl;

	char pass[2] = "X"; //when authenticating with API key in Freshdesk password is dummy password

	Request freshdesk(freshdesk_url, fr_buffer);
	freshdesk.addHeader("Content-Type: application/json");

	freshdesk.curl(getenv("FRESHDESK_TOKEN"), pass, contact_str);
	freshdesk.print();


	return 0;
}