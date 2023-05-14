#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <numeric>
#include "anime.h"

struct MyPrint {
	/// <summary>
	/// function call operator (). using ref& gettting accesss to function() get title and rating from param class
	/// </summary>
	/// <param name="Anime"> class anime </param>
	void operator()(const anime& Anime);
};

struct greater {
private:
	double rating;
public:
	/// <summary>
	/// constrct with param grater
	/// </summary>
	/// <param name="rating"> rating </param>
	greater(double rating);
	/// <summary>
	/// function call operator (). compare lhs value from anime class if it <(less) then rating value
	/// </summary>
	/// <param name="lhs"></param>
	/// <returns></returns>
	auto operator()(const anime& lhs) const;
};

struct MyBinOp {
private:
	size_t size;
public:
	/// <summary>
	/// 
	/// </summary>
	/// <param name="size"></param>
	explicit MyBinOp(size_t size);
	double operator()(double value, const anime& Anime) const;
};

struct MyUnaryOp {
	double operator()(const anime& Anime);
};

struct MyFunc {
private:
	double mean;
public:
	explicit MyFunc(double mean);
	double operator()(const double& rating) const;
};

int main() {
	std::array<anime, 8> animelist = {
		anime("One Piece", 8.68),
		anime("Spy x Family", 8.55),
		anime("Spy x Family", 8.55),
		anime("Kimi no Na wa", 8.85),
		anime("Nanatsu no Taizai", 7.69),
		anime("Space Cobra", 2.83),
		anime("Chi's Sweet Home", 5.21),
		anime("Keroro Gunsou", 5.2) };

	std::vector<anime> myanime(animelist.begin(), animelist.end());
	MyPrint print;
	//-------------------------------Task1 : FOR_EACH ------------------------------//
	std::cout << "\n";
	std::cout << "[1] Print my animelist using std::for_each with print()\n";
	std::cout << "\n";

	std::for_each(myanime.begin(), myanime.end(), print);
	std::cout << "--------------------------------------------------------------------";


	//-------------------------------Task2 : FIND_IF ------------------------------//
	std::cout << "\n";
	std::cout << "[2] Finding first anime rating from my animelist using std::find_if\n";
	std::cout << "\n";
	double value = 8;
	greater greater(value);
	auto find_greater = std::find_if(myanime.begin(), myanime.end(), greater);
	print(*find_greater);
	std::cout << "--------------------------------------------------------------------";

	//-------------------------------Task3 : ADJACENT_FIND ------------------------------//
	std::cout << "\n";
	std::cout << "[3] Finding animes with same name using std::adjacent_find\n";
	std::cout << "\n";
	auto found_adj = std::adjacent_find(myanime.begin(), myanime.end()); //finds the first two adjacent items that are equal , 
	if (found_adj != myanime.end()) print(*found_adj);
	else std::cout << "No adjacent in animelist \n";
	std::cout << "--------------------------------------------------------------------";


	//-------------------------------Task4 : EQUAL ------------------------------//
	std::cout << "\n";
	std::cout << "[4] \n";
	std::cout << "\n";
	if (std::equal(myanime.begin(), myanime.end(), animelist.begin())) //determines if two sets of elements are the same
		std::cout << "Equal!" << std::endl;
	else
		std::cout << "Not equal" << std::endl;
	std::cout << std::endl;
	std::cout << "--------------------------------------------------------------------";


	//-------------------------------Task5 : SEARCH ------------------------------//
	std::cout << "\n";
	std::cout << "[5] \n";
	std::cout << "\n";
	auto finding = std::search(myanime.begin(), myanime.end(), animelist.begin(), animelist.end()); //haystack = myanime ,neeedle = animelist , finding animelist in myanime
	if (finding != myanime.end()) {
		std::cout << "From index " << (finding - myanime.begin()) << " elemets is same "<< "\n";
	}
	else {
		std::cout << "Container 1 and container 2 had diffrence elements \n";
	}
	std::cout << "--------------------------------------------------------------------";


	//-------------------------------Task6 : AVERAGE ------------------------------//
	std::cout << "\n";
	std::cout << "[6] Finding average rating my animelist \n";
	std::cout << "\n";
	MyBinOp MBO(myanime.size());
	auto average = std::accumulate(myanime.begin(), myanime.end(), double(), MBO);
	std::cout << average << "\n";
	std::cout << "--------------------------------------------------------------------";


	//-------------------------------Task7 : TRANSFORM ------------------------------//
	std::cout << "\n";
	std::cout << "[7]  Use std::transform (create myanime_v2) \n";
	std::cout << "\n";
	std::vector<double> myanime_v2(animelist.size());
	MyUnaryOp MUO;
	std::transform(myanime.begin(), myanime.end(), myanime_v2.begin(), MUO); //[1] deref myanime, then implicit converting type myanime. target myanimev2 type converted return type of MUO
	std::copy(myanime_v2.begin(), myanime_v2.end(), std::ostream_iterator<double>(std::cout, "\n"));
	std::cout << "--------------------------------------------------------------------";


	//-------------------------------Task8 : TRANSFORM ------------------------------//
	std::cout << "\n";
	std::cout << "[8]  Use std::transform (transform v2 values) \n";
	std::cout << "\n";
	MyFunc func(average);
	std::transform(myanime_v2.begin(), myanime_v2.end(), myanime_v2.begin(), func); //[1]
	std::copy(myanime_v2.begin(), myanime_v2.end(), std::ostream_iterator<double>(std::cout, "\n"));
	std::cout << "--------------------------------------------------------------------";


	//-------------------------------Task9 : SORT ------------------------------//
	std::cout << "\n";
	std::cout << "[9]  Use std::sort \n";
	std::cout << "\n";
	std:sort(myanime_v2.begin(), myanime_v2.end(), [](const double& a, const double& b) { return a < b; });
	std::copy(myanime_v2.begin(), myanime_v2.end(), std::ostream_iterator<double>(std::cout, "\n"));
	std::cout << "--------------------------------------------------------------------";


	return 0; 
}

void MyPrint::operator()(const anime& Anime) {
	std::cout <<"Title: " << Anime.get_title() << " Rating : " << Anime.get_rating() << "\n";
}

greater::greater(double rating) : rating(rating){
}

auto greater::operator()(const anime& lhs) const {
	return lhs.get_rating() > rating;
}

MyBinOp::MyBinOp(size_t size) : size(size) {

}
double MyBinOp::operator()(double value, const anime& Anime) const {
	return value += Anime.get_rating() / size;
}

double MyUnaryOp::operator()(const anime& Anime) {
	return Anime.get_rating() * 2;
}

MyFunc::MyFunc(double mean) : mean(mean) {
}

double MyFunc::operator()(const double& rating) const{
	return rating + mean;
}
