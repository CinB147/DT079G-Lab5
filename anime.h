#pragma once
#ifndef ANIME_H
#define ANIME_H

#include <iostream>

class anime {
private:
	std::string title;
	double rating;
public:
	/// <summary>
	/// construct with param 
	/// </summary>
	/// <param name="title"> this*title </param>
	/// <param name="rating"> this* rating</param>
	anime(std::string title, double rating);
	/// <summary>
	/// operator overloading ==. return ture or false if name from rhs (anime class) is same as title
	/// </summary>
	/// <param name="rhs"></param>
	/// <returns></returns>
	bool operator==(const anime& rhs);
	/// <summary>
	/// get object title
	/// </summary>
	/// <returns> title </returns>
	std::string get_title();
	/// <summary>
	/// get object rating
	/// </summary>
	/// <returns> rating </returns>
	double get_rating();
	/// <summary>
	/// const version of get_title func()
	/// </summary>
	/// <returns></returns>
	std::string get_title() const;
	/// <summary>
	/// const version of get_rating func()
	/// </summary>
	/// <returns></returns>
	double get_rating() const;

};

#endif // !ANIME_H

