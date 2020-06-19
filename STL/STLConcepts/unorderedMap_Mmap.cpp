#include <iostream>
#include <unordered_map>

#define LOG(x) std::cout << #x << ":" << x << std::endl;

class Entity
{
	const char* m_name;
public:
	Entity()
	{
		std::cout << "Constructor called." << std::endl;
	}
	Entity(const char* name) {
		std::cout << "Constructor called parameter." << std::endl;
		m_name = name;
	}
	~Entity() {}
	const char* getName() {
		return m_name;
	}
};

void ideaOfUnorderedMap()
{
	std::unordered_map<int, Entity> uMap;
	LOG(uMap.max_load_factor());
	LOG(uMap.load_factor());
	LOG(uMap.size());
	LOG(uMap.bucket_count());

	Entity e = Entity("xyz");
	uMap[12] = e;
	std::cout << uMap[12].getName() << std::endl;

	uMap.insert(std::pair<int, Entity>(1,Entity("pqr")));

	std::cout << "Elements of the unordred map:" << std::endl;

	for (auto itr = uMap.begin(); itr != uMap.end(); ++itr) {
		std::cout << itr->first << ":" << itr->second.getName() << std::endl;
	}
	LOG(uMap.max_load_factor());
	LOG(uMap.load_factor());
	LOG(uMap.size());
	LOG(uMap.bucket_count());

	e = Entity("xyz");
	uMap[12] = e;
	e = Entity("34z");
	uMap[1] = e;
	e = Entity("u23");
	uMap[10] = e;
	e = Entity("xyz");
	uMap[9] = e;
	e = Entity("xyz");
	uMap[78] = e;
	//in place construction
	uMap.emplace(75, "jskdj");

	std::cout << "Elements of the unordred map:" << std::endl;

	for (auto itr = uMap.begin(); itr != uMap.end(); ++itr) {
		std::cout << itr->first << ":" << itr->second.getName() << std::endl;
	}
	LOG(uMap.max_load_factor());
	LOG(uMap.load_factor());
	LOG(uMap.size());
	LOG(uMap.bucket_count());

	for (auto& ele : uMap) {
		std::cout << "Elements " << ele.first << "  is in bucket " << uMap.bucket(ele.first) << std::endl;
	}

	for (int i = 0; i < uMap.bucket_count(); ++i) {
		std::cout << "Elements in bucket " << i << " is/are " << uMap.bucket_size(i) << std::endl;
	}

}

void ideaOfUnorderedMultiMap()
{
	//Below refernce for why the ket_equal is used and how can we have custom classes as the key
	//https://stackoverflow.com/questions/17016175/c-unordered-map-using-a-custom-class-type-as-the-key#

	std::unordered_multimap<int, Entity> uMMap;

	uMMap.insert(std::pair<int, Entity>(34, Entity("fdhs"))); //all such calls, call constructor only once as it will invoke RValue reference constructor
	uMMap.insert(std::pair<int, Entity>(21, Entity("hagf")));

	uMMap.insert(std::pair<int, Entity>(1, Entity("kjsfk")));
	uMMap.insert(std::pair<int, Entity>(34, Entity("jkksddfk")));

	uMMap.emplace(34, "hsdfjter"); //this call will build inplace object even without std::move

	//below is not allowed for obvious reasons
	//uMMap[67] = Entity("yu");

	std::cout << "Elements of the unordred multi-map:" << std::endl;

	for (auto itr = uMMap.begin(); itr != uMMap.end(); ++itr) {
		std::cout << itr->first << ":" << itr->second.getName() << std::endl;
	}

	for (auto& ele : uMMap) {
		std::cout << "Elements " << ele.first << "  is in bucket " << uMMap.bucket(ele.first) << std::endl;
	}

	for (int i = 0; i < uMMap.bucket_count(); ++i) {
		std::cout << "Elements in bucket " << i << " is/are " << uMMap.bucket_size(i) << std::endl;
	}

	auto its = uMMap.equal_range(34);
	for (auto itr = its.first; itr != its.second; ++itr) {
		std::cout << "Value for key 34:" << itr->second.getName() << std::endl;
	}

	LOG(uMMap.max_load_factor());
	LOG(uMMap.load_factor());
	LOG(uMMap.size());
	LOG(uMMap.bucket_count());
}