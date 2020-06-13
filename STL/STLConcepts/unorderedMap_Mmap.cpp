#include <iostream>
#include <unordered_map>

#define LOG(x) std::cout << #x << ":" << x << std::endl;

class Entity
{
	const char* m_name;
public:
	Entity()
	{}
	Entity(const char* name) {
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

	std::cout << "Elements of the unordred map:" << std::endl;

	for (auto itr = uMap.begin(); itr != uMap.end(); ++itr) {
		std::cout << itr->first << ":" << itr->second.getName() << std::endl;
	}
	LOG(uMap.max_load_factor());
	LOG(uMap.load_factor());
	LOG(uMap.size());
	LOG(uMap.bucket_count());


}