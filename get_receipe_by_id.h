#ifndef INCLUDED_GET_RECEIPE_BY_ID
#define INCLUDED_GET_RECEIPE_BY_ID

#include <cpr/cpr.h>
#include <iostream>
#include <string.h>
#include <nlohmann/json.hpp>

namespace grbId
{
    class getRecipeById
    {
    public:
        std::string makeReq(std::string req);
    } obj;

    std::string getRecipeById::makeReq(std::string req)
    {

        // making the url by concatenating
        std::string url = "https://api.spoonacular.com/recipes/" + req + "/information?includeNutrition=false";
        std::cout << "Link-> " << url << std::endl;

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
            std::cout << "Response from get_reciepe_by_id API" << std::endl;
            return r.text;
        }
    }
}

#endif