#include "anime.h"

anime::anime(std::string title, double rating) : title(title), rating(rating){

}

bool anime::operator==(const anime& rhs) {
	return title == rhs.title;
}

std::string anime::get_title() {
	return title;
}

double anime::get_rating() {
	return rating;
}

std::string anime::get_title() const {
	return title;
}
double anime::get_rating() const {
	return rating;
}


