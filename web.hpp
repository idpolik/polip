#include <Windows.h>
#include <WinINet.h>
#include <regex>
#pragma comment(lib, "wininet.lib")

std::string makeRequest(std::string webUrl) {
	HINTERNET netHandler = InternetOpenA("Mozilla/5.0", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, NULL);
	HINTERNET urlFile;
	std::string response;
	if (netHandler) 
	{
		urlFile = InternetOpenUrlA(netHandler, webUrl.c_str(), NULL, NULL, NULL, NULL);
		if (urlFile) 
		{
			char buffer[2048];
			DWORD bytesRead;
			do 
			{
				InternetReadFile(urlFile, buffer, 2048, &bytesRead);
				response.append(buffer, bytesRead);
				memset(buffer, 0, 2048);
			} 
			while (bytesRead);
			InternetCloseHandle(netHandler);
			InternetCloseHandle(urlFile);
			return response;
		}
	}
}

std::string grabApi(std::string api) {
	std::string webContents = makeRequest(api.c_str());
	return webContents;
}

std::string formatApiRequest(std::string og)
{
	std::string replaceSlash = "%2F";
	std::string replaceColon = "%3A";
	std::string str = og;
	str = std::regex_replace(str, std::regex("/"), replaceSlash);
	str = std::regex_replace(str, std::regex(":"), replaceColon);

	return str;
}