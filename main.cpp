

#include <iostream>
#include "web.hpp"
#include "json.hpp"

int main()
{
    const std::string apiKey = "[GOOGLE-CIVIC-API-KEY-HERE]";
    const std::string electionsGlobalApi = std::string("https://www.googleapis.com/civicinfo/v2/elections?key=" + apiKey);
    const std::string legislatorApiBase = std::string("https://www.googleapis.com/civicinfo/v2/representatives/");
    

    std::string electionsRaw = grabApi(electionsGlobalApi);
    nlohmann::json electionsJson = nlohmann::json::parse(electionsRaw);


    std::vector<std::string> electionNames;
    std::vector<std::string> electionDates;
    std::vector<std::string> electionID;
    std::vector<std::string> electionDistrictID;
    

    for (auto& election : electionsJson["elections"])
    {
        if (election["id"] != "2000")
        {
            electionNames.push_back(election["name"]);
            electionDates.push_back(election["electionDay"]);
            electionID.push_back(election["id"]);



            electionDistrictID.push_back(election["ocdDivisionId"]);
        }
        
    }

    for (int i = 0; i < electionID.size(); i++)
    {
        std::cout << electionNames.at(i) + " will be on " + electionDates.at(i) + " using ID: " + electionID.at(i) + "\n";
    }
    

    std::cout << ("\n\n\n\n");

    std::vector<std::string> legislatorNames;
    std::vector<std::string> legislatorAffiliations;

    for (int i = 0; i < electionDistrictID.size(); i++)
    {
        std::string legislationRaw = grabApi(legislatorApiBase
            + formatApiRequest(electionDistrictID.at(i))
            + "?roles=legislatorUpperBody&key="
            + apiKey);
        nlohmann::json legislationJson = nlohmann::json::parse(legislationRaw);
        for (auto& legislator : legislationJson["officials"])
        {
            legislatorNames.push_back(legislator["name"]);
            legislatorAffiliations.push_back(legislator["party"]);   
        }
        

    }
    for (int i = 0; i < legislatorNames.size(); i++)
    {
        std::cout << "Senator " + legislatorNames.at(i) + " is a member of the  " + legislatorAffiliations.at(i) + "\n";
    }
}
