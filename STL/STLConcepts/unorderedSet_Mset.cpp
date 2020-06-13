#include <iostream>
#include <unordered_set>
#include <algorithm>

#define LOG(x) std::cout << #x << ":" << x << std::endl

void ideaOfUnorderedSet()
{
	//Unordered sets are containers that store unique elements in no particular order, and which allow for fast retrieval 
	//of individual elements based on their value.
	//In an unordered_set, the value of an element is at the same time its key, that identifies it uniquely.Keys are immutable, 
	//therefore, the elements in an unordered_set cannot be modified once in the container - they can be inserted and removed, though.

	//Internally, the elements in the unordered_set are not sorted in any particular order, but organized into buckets depending on 
	//their hash values to allow for fast access to individual elements directly by their values 
	//(with a constant time complexity on average).

	std::unordered_set<int> unorSet; //We can also provide our own hash-function and key_equal functions.

	unorSet.insert(20);
	unorSet.insert(-10);
	unorSet.insert(40);
	unorSet.insert(0);
	unorSet.insert(0);
	unorSet.insert(5);
	unorSet.insert(8);
	unorSet.insert(-30);

	std::cout << "Size of the unordered_set:" << unorSet.size() << std::endl;
	std::cout << "Elements of the unordered_set (duplicates elements can not be inserted). unordered_set does not follow any order \
		while arranging its element, neither sorted nor order of insertion." << std::endl;

	for (std::unordered_set<int>::iterator it = unorSet.begin(); it != unorSet.end(); ++it) {
		std::cout << *it << "," << std::endl;
		//*it = 8; //not possible as with normal <set>.
	}

	std::cout << "Removing 0 from the unordered_set." << std::endl;
	unorSet.erase(0);

	std::cout << "Size of the unordered_set:" << unorSet.size() << std::endl;
	std::cout << "Elements of the unordered_set (duplicates elements can not be inserted)." << std::endl;

	for (std::unordered_set<int>::iterator it = unorSet.begin(); it != unorSet.end(); ++it) {
		std::cout << *it << "," << std::endl;
		//*it = 8; //not possible as with normal <set>.
	}

	std::unordered_set<int>::iterator it = unorSet.find(5);
	if (it != unorSet.end()) {
		std::cout << "Element 5 found (must be const run time)." << std::endl;
		++it;
		std::cout << "Next element is (not in any specific order, only the order in which they got arranged in the container right now):" 
			<< *it << "." << std::endl;
	}


	//#Iterators
	//std::unordered_set<int>::iterator it = unorSet.rbegin(); There is no reverse iterator, at least mendated by the C++ statndard.

	//#bukets
	int sz = unorSet.size();
	int bucketCount = unorSet.bucket_count();
	LOG(sz);
	LOG(bucketCount);
	//unordered_set containers internally maintain a hash, made of buckets. Each bucket corresponds to particular has value. 
	//Elements are stored in these buckets based on their has values.
	for (int i : unorSet) {
		std::cout << "Element " << i << " is sotred in bucket #" << unorSet.bucket(i) << std::endl;
	}
	for (int i = 0; i < bucketCount; ++i) {
		std::cout << "Number of elements in bucket " << i << " is " << unorSet.bucket_size(i) << std::endl;
	}
	double loadFactor = unorSet.load_factor(); //tells the current accomodation load in buckets => size/bucket_count
	double maxLoadFactor = unorSet.max_load_factor(); //allowed max load factor
	int maxBucketCount = unorSet.max_bucket_count();
	int maxSize = unorSet.max_size();
	
	LOG(loadFactor);
	LOG(maxLoadFactor);
	LOG(maxBucketCount);
	LOG(maxSize);

	//#Playing with the buckets
	unorSet.rehash(11); //Making total buckets to 11 or more, this will invalidate all the iteratores as position of all the elements will be redetrmind.
	sz = unorSet.size();
	bucketCount = unorSet.bucket_count();
	LOG(sz);
	LOG(bucketCount);

	//Sets the number of buckets in the container (bucket_count) to the most appropriate to contain at least n elements.
	//If n is greater than the current bucket_count multiplied by the max_load_factor, the container's bucket_count is increased and a rehash is forced.

	unorSet.reserve(16);	//reserving the number of elements, not the bucket_count
	sz = unorSet.size();
	bucketCount = unorSet.bucket_count();
	LOG(sz);
	LOG(bucketCount);

	unorSet.reserve(20);
	sz = unorSet.size();
	bucketCount = unorSet.bucket_count();
	LOG(sz);
	LOG(bucketCount);

	//unorSet.max_load_factor(unorSet.max_load_factor() / 2.0);
	unorSet.insert(10);
	unorSet.insert(60);
	unorSet.insert(53);
	unorSet.insert(84);
	unorSet.insert(-340);
	unorSet.insert(130);
	unorSet.insert(603);
	unorSet.insert(533);
	unorSet.insert(843);
	unorSet.insert(-3430);
	unorSet.insert(536);
	unorSet.insert(864);
	unorSet.insert(-3406);
	unorSet.insert(1306);
	unorSet.insert(6603);
	unorSet.insert(6533);
	unorSet.insert(8643);
	unorSet.insert(-36430);

	//change the max_load_factor to half of the current value
	unorSet.max_load_factor(unorSet.max_load_factor()/2.0); //It may or may not inititate rehash.
	//unorSet.reserve(20);
	sz = unorSet.size();
	bucketCount = unorSet.bucket_count();
	loadFactor = unorSet.load_factor();
	maxLoadFactor = unorSet.max_load_factor();
	LOG(sz);
	LOG(bucketCount);
	LOG(loadFactor);
	LOG(maxLoadFactor);


	std::cout << "Currently " << (unorSet.empty() ? "unordered_set is empty." : "unordered_set is not empty.") << std::endl;

	std::cout << "Clearning unordered_set." << std::endl;
	unorSet.clear();
	std::cout << "Currently " << (unorSet.empty() ? "unordered_set is empty." : "unordered_set is not empty.") << std::endl;

}

struct Equal
{
	bool operator()(const int& a, const int& b) const
	{
		std::cout << "Our operator got called." << std::endl;
		return true;
		//return false;
	}
};

void ideaOfUnorderedMultiSet()
{
	std::unordered_multiset<int> unOrMSet; //We can also provide our own hash-function and key_equal functions.

	unOrMSet.insert(78);
	unOrMSet.insert(67);
	unOrMSet.insert(1);
	unOrMSet.insert(67);
	unOrMSet.insert(67);
	unOrMSet.insert(0);
	unOrMSet.insert(10);
	unOrMSet.insert(10);
	unOrMSet.insert(6);

	std::unordered_multiset<int>::iterator itr = unOrMSet.begin();
	std::cout << "Elements of the unordered multiset:" << std::endl;
	for (; itr != unOrMSet.end(); ++itr) {
		std::cout << " " << *itr;
	}
	std::cout << std::endl;

	int size = unOrMSet.size();
	int totalBuckets = unOrMSet.bucket_count();
	double loadFactor = unOrMSet.load_factor(); //tells the current accomodation load in buckets => size/bucket_count

	LOG(size);
	LOG(totalBuckets);
	LOG(loadFactor);

	double maxLoadFactor = unOrMSet.max_load_factor(); //allowed max load factor
	int maxBucketCount = unOrMSet.max_bucket_count();
	int maxSize = unOrMSet.max_size();


	LOG(maxLoadFactor);
	LOG(maxBucketCount);
	LOG(maxSize);

	std::unordered_multiset<int>::iterator it = unOrMSet.find(67);
	if (it != unOrMSet.end())
		std::cout << "Found 67." << std::endl;

	std::cout << "Total number of 67s " << unOrMSet.count(67) << std::endl;
	std::cout << "67 over range:" << std::endl;
	std::pair<std::unordered_multiset<int>::iterator, std::unordered_multiset<int>::iterator> iteq = unOrMSet.equal_range(67);
	std::unordered_multiset<int>::iterator it2 = iteq.first;
	for (; it2 != iteq.second; ++it2) {
		std::cout << " " << *(it2) << "(b:" << unOrMSet.bucket(67) << ")";
	}
	std::cout << std::endl;

	for (int i = 0; i < unOrMSet.bucket_count(); ++i) {
		std::cout << "Elements in bucket " << i << " " << unOrMSet.bucket_size(i) << std::endl;
	}

	unOrMSet.erase(67);

	itr = unOrMSet.begin();
	std::cout << "Elements of the unordered multiset after erasing 67:" << std::endl;
	for (; itr != unOrMSet.end(); ++itr) {
		std::cout << " " << *itr;
	}
	std::cout << std::endl;


	std::cout << "After rehasing attempt:" << std::endl;
	unOrMSet.rehash(120);

	size = unOrMSet.size();
	totalBuckets = unOrMSet.bucket_count();
	loadFactor = unOrMSet.load_factor(); //tells the current accomodation load in buckets => size/bucket_count

	LOG(size);
	LOG(totalBuckets);
	LOG(loadFactor);

	

	std::unordered_multiset<int,std::hash<int>, Equal> experiment;
	//Observations:
	//Equal to operator playes a role along with hash function while finding values.
	//When we insert a value, an hash is calculated based on the value and then it is inserted in the matching bucket. While inserting it also looks
	//if other values in that bucket are equal or not, if they are equal (evaluated by Equal) then it probably keeps them sequenced based on the value of
	//Equal().
	//When we query a value, its hash is calulated and bucket is located and then Equal functor is used to identiy the value. (If our Equal 
	//always returns false then query will not return anything. And if it always returns true then it will return everything in that bucket.)

	//So basically hashing is different and identifying equal elements is a different thing.
	//When two different key results in the same hash value, their collision is handled indpendent of being equal by equal_key. equal_key comes into picture
	//for querying or arranging the elements in the same bucket during collisioned-insertion.

	//Suppose we return always true from Equal, then when we query 8, its hash is first calculated and then once the bucket is located then Equal is
	//used to identify the equal elements and return. So if we are returning true for eveything it does not mean equal range will return iterators for
	//all the elements.
	

	experiment.insert(8);
	experiment.insert(89);
	experiment.insert(10000);
	experiment.insert(5849);
	experiment.insert(-19902);
	experiment.insert(998); //This value causes collision and Equal functor is called, and they are kept in the same bucket too.



	for (int i = 0; i < experiment.bucket_count(); ++i) {
		std::cout << "Elements in bucket " << i << " " << experiment.bucket_size(i) << std::endl;
	}

	//In the below line when we query for 998, for which we saw collision, we get iterator for all the values in the same bucket, which has the 
	//same hash value too.

	std::pair<std::unordered_multiset<int, std::hash<int>, Equal>::iterator, std::unordered_multiset<int, std::hash<int>, Equal>::iterator> iteq2 = experiment.equal_range(998);
	std::unordered_multiset<int, std::hash<int>, Equal>::iterator it3 = iteq2.first;
	for (; it3 != iteq2.second; ++it3) {
		std::cout << " " << *(it3) << "(b:" << experiment.bucket(998) << ")";
	}
	std::cout << std::endl;

}
