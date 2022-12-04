#include <cpr/cpr.h>
#include <iostream>
#include <string>

/// @brief Function to make the ingredients part of url, by iterating over the ingredients array got from frontend
/// @param arr
/// @return partUrl
std::string urlmaker(std::string arr[], int l)
{
    std::string partUrl = "";
    for (int i = 0; i < l; i++)
        partUrl += arr[i] + ",";
    // to pop the extra comma at the end
    partUrl.pop_back();
    return partUrl;
}

int main(int argc, char **argv)
{
    // Ingredients array coming from frontend
    std::string ingri[3] = {"carrots", "tomatoes", "capsicum"};
    int len = sizeof(ingri) / sizeof(ingri[0]);
    // making the url by concatenating
    std::string url = "https://api.spoonacular.com/recipes/findByIngredients?ingredients=" + urlmaker(ingri, len) + "&number=10&limitLicense=true&ranking=1&ignorePantry=false";

    // actual GET request to spoonacular API
    cpr::Response r = cpr::Get(cpr::Url{url},
                               cpr::Header{{"x-api-key", "fc5e4dba84304af9a502a94407b466e7"}});
    // error handling
    if (r.status_code == 0)
        std::cerr << r.error.message << std::endl;
    else if (r.status_code >= 400)
    {
        std::cerr << "Error [" << r.status_code << "] making request" << std::endl;
    }
    else
    {
        std::cout << "Request took " << r.elapsed << std::endl;
        std::cout << "Response from API..." << std::endl;
        // nlohmann::json j = nlohmann::json::parse(r.text);
        // std::cout << "Activity: " << j["activity"] << std::endl;
        // std::cout << "Type: " << j["type"] << std::endl;
        // std::cout << "Participants: " << j["participants"] << std::endl;
        // std::cout << "Price: " << j["price"] << std::endl;
        // std::cout << "Link: " << j["link"] << std::endl;
        // std::cout << "Key: " << j["key"] << std::endl;
        // std::cout << "Accessibility: " << j["accessibility"] << std::endl;
        std::cout << "Body:" << std::endl;
        std::cout << r.text << std::endl;
    }
    return 0;
}