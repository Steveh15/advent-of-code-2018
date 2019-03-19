



#include <iostream>
#include <vector>
#include <string>

using namespace std;

class AddressBook
{
    public:
    // using a template allows us to ignore the differences between functors, function pointers 
    // and lambda
    template<typename Func>
    std::vector<std::string> findMatchingAddresses (Func func)
    { 
        std::vector<std::string> results;
        for ( auto itr = _addresses.begin(), end = _addresses.end(); itr != end; ++itr )
        {
            // call the function passed into findMatchingAddresses and see if it matches
            if ( func( *itr ) )
            {
                results.push_back( *itr );
            }
        }
        return results;
    }


    void addAddress(std::string address){
    	_addresses.push_back(address);
    }


    private:
    std::vector<std::string> _addresses;
};

AddressBook global_address_book;

vector<string> findAddressesFromOrgs ()
{
    return global_address_book.findMatchingAddresses( 
        // we're declaring a lambda here; the [] signals the start
        [] (const string& addr) { return addr.find( ".org" ) != string::npos; } 
    );
}

int main(){


	AddressBook myBook;
	myBook.addAddress("stephen.c.mackie@gmail.com");
	myBook.addAddress("Bephen.c.mackie@gmail.com");
	myBook.addAddress("ASDsada@gmail.com");
	myBook.addAddress("stephen.c.mackie@gmail.org");


	auto func = [] () { std::cout << "Hello world"; };
    func(); // now call the function

  

}