#ifndef INCLUDED_GET_RECEIPE_BY_INGRI
#define INCLUDED_GET_RECEIPE_BY_INGRI

#include <cpr/cpr.h>
#include <iostream>
#include <string.h>
#include <nlohmann/json.hpp>
#include <sstream>

namespace grbIngri
{
    class getRecipeByIngri
    {
    public:
        static std::string makeReq(std::string ingri);
    } obj;

    /// @brief Function to make the ingredients part of url, by iterating over the ingredients array got from frontend
    /// @param arr
    /// @return partUrl
    std::string getRecipeByIngri::makeReq(std::string ingri)
    {
        nlohmann::json j;
        // making the url by concatenating
        // std::string url = "https://api.spoonacular.com/recipes/findByIngredients?ingredients=" + obj.urlmaker(ingri, len) + "&number=30&limitLicense=true&ranking=2&ignorePantry=false";
        std::string url = "https://api.spoonacular.com/recipes/findByIngredients?ingredients=" + ingri + "&number=20&limitLicense=true&ranking=2&ignorePantry=false";

        // actual GET request to spoonacular API
        cpr::Response r = cpr::Get(cpr::Url{url},
                                   cpr::Header{{"x-api-key", "fc5e4dba84304af9a502a94407b466e7"}});
        // error handling
        if (r.status_code == 0)
        {
            std::cerr << r.error.message << std::endl;
            return "";
        }
        else if (r.status_code >= 400)
        {
            std::cerr << "Error [" << r.status_code << "] making request" << std::endl;
            return "";
        }
        else
        {
            std::cout << "Request took " << r.elapsed << std::endl;
            std::cout << "Response from get_reciepe_by_ingrideints API" << std::endl;
            j["body"] = r.text;
            return r.text;
        }
    }
}

#endif