#ifndef ATLAS_H
#define ATLAS_H
#include<iostream>
#include<string>
#include<graphics.h>
#include<vector>
class atlas {
public:
	atlas(std::string path1, int num1);
	atlas(atlas* src);
	~atlas();
	void clear() {
		for (auto img : frame_list) {
			if (img) delete img;
		}
		frame_list.clear();
		num = 0;
	}
	int get_size() {
		return (int)frame_list.size();
	}
	IMAGE* get_image(const int idx) {
		if (idx < 0 || idx >= (int)frame_list.size()) {
			return nullptr;
		}
		return frame_list[idx];
	}
	void add_image( IMAGE* img) {
		frame_list.push_back(img);
	}
	friend class animation;
private:
	std::string path;
	int num = 0;
	std::vector<IMAGE*> frame_list;
};
#endif
