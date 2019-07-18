#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

#include "include/get_input.hpp"

class Metadata{

public:
	std::vector<Metadata> child_nodes;
	std::vector<int> metadata;

	Metadata(std::vector<int>::iterator & it){
		int child_nodes_n = *it++;
		int metadata_entries_n = *it++;

		for(int i = 0 ; i < child_nodes_n ; i++)
			child_nodes.push_back(Metadata(it));
		for(int i = 0 ; i < metadata_entries_n ; i++)
			metadata.push_back(*it++);
	}

	static int SumMetadata(const Metadata & m){
		int sum = std::accumulate(m.metadata.begin(), m.metadata.end(),0);
		int sum_children = std::accumulate(m.child_nodes.begin(), m.child_nodes.end(), 0, [](int sum, Metadata a){
			return sum + SumMetadata(a);
		});
		return sum + sum_children;
	}

	static int SumMetadataAlt(const Metadata & m){
		if(m.child_nodes.size() == 0){
			return SumMetadata(m);
		}
		else{
			std::vector<int> indexes = m.metadata;
			indexes.erase(std::remove_if(indexes.begin(), indexes.end(), [m](int a){
				return a > (m.child_nodes.size());
			}),indexes.end());

			int sum = 0;
			for(auto i : indexes){
				Metadata temp = m.child_nodes[i-1];
				 sum += SumMetadataAlt(temp);
			}
			return sum;
		}
	}

};




int main(){
	std::vector<int> input(get_input<int>("day08.txt"));
	auto it = input.begin();
	Metadata root(it);

	std::cout << "Part one solution : " << Metadata::SumMetadata(root) << "\n";
	std::cout << "Part two solution : " << Metadata::SumMetadataAlt(root) << "\n";

	return 0;
}


