#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <cstdlib>

class Point {
public:
    int x_, y_;
    Point(int x, int y) : x_(x), y_(y) {}
};

class Line {
public:
    Point start_;
    char dir_;
    int length_;
    Line(Point start, char dir, int length) : start_(start), dir_(dir), length_(length) {}
};

int main() {
    std::cout << "Day 3, Part 1\n";
    std::ifstream input_file("inputs/d3.txt");

    std::vector<std::string> commands[2];
    std::vector<Line> lines[2];
    std::string command;
    std::string line;
    while(std::getline(input_file, line, '\n')) {
        static int i = 0;
        std::stringstream input_string(line);
        while(std::getline(input_string, command, ',')) {
            commands[i].push_back(command);
        }
        ++i;
    }
    input_file.close();

    for (int j = 0; j < 2; j++) {
        int x = 0;
        int y = 0;
        for (int i = 0; i < commands[j].size(); ++i) {
            char direction = commands[j][i][0];
            int length = std::stoi(commands[j][i].substr(1));
            lines[j].push_back(Line(Point(x, y), direction, length));
            switch (direction) {
                case 'R':
                    x += length;
                    break;
                case 'L':
                    x -= length;
                    break;
                case 'U':
                    y += length;
                    break;
                case 'D':
                    y -= length;
                    break;
            }
        }
    }

    std::vector<Point> cross_points;
    for (int i = 0; i < lines[0].size(); ++i) {
        for (int j = 0; j < lines[1].size(); ++j) {
            switch (lines[0][i].dir_) {
                case 'R':
                    if (lines[1][j].dir_ == 'U') {
                        if (
                            lines[1][j].start_.x_ >= lines[0][i].start_.x_ && 
                            lines[1][j].start_.x_ <= lines[0][i].start_.x_ + lines[0][i].length_
                        ) {
                            if (
                                lines[1][j].start_.y_ <= lines[0][i].start_.y_ && 
                                lines[1][j].start_.y_ + lines[1][j].length_ >= lines[0][i].start_.y_
                            ) {
                                cross_points.push_back(Point(lines[1][j].start_.x_, lines[0][i].start_.y_));
                            }
                        }
                    } else if (lines[1][j].dir_ == 'D') {
                        if (
                            lines[1][j].start_.x_ >= lines[0][i].start_.x_ && 
                            lines[1][j].start_.x_ <= lines[0][i].start_.x_ + lines[0][i].length_
                        ) {
                            if (
                                lines[1][j].start_.y_ >= lines[0][i].start_.y_ && 
                                lines[1][j].start_.y_ - lines[1][j].length_ <= lines[0][i].start_.y_
                            ) {
                                cross_points.push_back(Point(lines[1][j].start_.x_, lines[0][i].start_.y_));
                            }
                        }
                    }
                    break;
                case 'L':
                    if (lines[1][j].dir_ == 'U') {
                        if (
                            lines[1][j].start_.x_ <= lines[0][i].start_.x_ && 
                            lines[1][j].start_.x_ >= lines[0][i].start_.x_ - lines[0][i].length_
                        ) {
                            if (
                                lines[1][j].start_.y_ <= lines[0][i].start_.y_ && 
                                lines[1][j].start_.y_ + lines[1][j].length_ >= lines[0][i].start_.y_
                            ) {
                                cross_points.push_back(Point(lines[1][j].start_.x_, lines[0][i].start_.y_));
                            }
                        }
                    } else if (lines[1][j].dir_ == 'D') {
                        if (
                            lines[1][j].start_.x_ <= lines[0][i].start_.x_ && 
                            lines[1][j].start_.x_ >= lines[0][i].start_.x_ - lines[0][i].length_
                        ) {
                            if (
                                lines[1][j].start_.y_ >= lines[0][i].start_.y_ && 
                                lines[1][j].start_.y_ - lines[1][j].length_ <= lines[0][i].start_.y_
                            ) {
                                cross_points.push_back(Point(lines[1][j].start_.x_, lines[0][i].start_.y_));
                            }
                        }
                    }
                    break;
                case 'U':
                    if (lines[1][j].dir_ == 'R') {
                        if (
                            lines[1][j].start_.x_ <= lines[0][i].start_.x_ && 
                            lines[1][j].start_.x_ + lines[1][j].length_ >= lines[0][i].start_.x_
                        ) {
                            if (
                                lines[1][j].start_.y_ >= lines[0][i].start_.y_ && 
                                lines[1][j].start_.y_ <= lines[0][i].start_.y_ + lines[0][i].length_
                            ) {
                                cross_points.push_back(Point(lines[0][i].start_.x_, lines[1][j].start_.y_));
                            }
                        }
                    } else if (lines[1][j].dir_ == 'L') {
                        if (
                            lines[1][j].start_.x_ >= lines[0][i].start_.x_ && 
                            lines[1][j].start_.x_ - lines[1][j].length_ <= lines[0][i].start_.x_
                        ) {
                            if (
                                lines[1][j].start_.y_ >= lines[0][i].start_.y_ && 
                                lines[1][j].start_.y_ <= lines[0][i].start_.y_ + lines[0][i].length_
                            ) {
                                cross_points.push_back(Point(lines[0][i].start_.x_, lines[1][j].start_.y_));
                            }
                        }
                    }
                    break;
                case 'D':
                    if (lines[1][j].dir_ == 'R') {
                        if (
                            lines[1][j].start_.x_ <= lines[0][i].start_.x_ && 
                            lines[1][j].start_.x_ + lines[1][j].length_ >= lines[0][i].start_.x_
                        ) {
                            if (
                                lines[1][j].start_.y_ <= lines[0][i].start_.y_ && 
                                lines[1][j].start_.y_ >= lines[0][i].start_.y_ - lines[0][i].length_
                            ) {
                                cross_points.push_back(Point(lines[0][i].start_.x_, lines[1][j].start_.y_));
                            }
                        }
                    } else if (lines[1][j].dir_ == 'L') {
                        if (
                            lines[1][j].start_.x_ >= lines[0][i].start_.x_ && 
                            lines[1][j].start_.x_ - lines[1][j].length_ <= lines[0][i].start_.x_
                        ) {
                            if (
                                lines[1][j].start_.y_ <= lines[0][i].start_.y_ && 
                                lines[1][j].start_.y_ >= lines[0][i].start_.y_ - lines[0][i].length_
                            ) {
                                cross_points.push_back(Point(lines[0][i].start_.x_, lines[1][j].start_.y_));
                            }
                        }
                    }
                    break;
            }
        }
    }

    std::cout << "No. of cross_points: " << cross_points.size() << "\n";

    int best_distance = 100000000;
    for (Point p : cross_points) {
        int newdist = std::abs(p.x_) + std::abs(p.y_);
        if (newdist < best_distance) {
            best_distance = newdist;
        }
    }
    
    std::cout << best_distance << "\n";

    std::cout << "Day 3, Part 2\n";
    int best_sum = 100000000;
    for (int j = 0; j < cross_points.size(); ++j) {
        int path0 = 0;
        for (int i = 0; i < lines[0].size(); ++i) {
            if (
                lines[0][i].dir_ == 'R' &&
                cross_points[j].x_ >= lines[0][i].start_.x_ &&
                cross_points[j].x_ <= lines[0][i].start_.x_ + lines[0][i].length_ &&
                cross_points[j].y_ == lines[0][i].start_.y_
            ) {
                path0 += cross_points[j].x_ - lines[0][i].start_.x_;
                break;
            } else if (
                lines[0][i].dir_ == 'L' &&
                cross_points[j].x_ <= lines[0][i].start_.x_ &&
                cross_points[j].x_ >= lines[0][i].start_.x_ - lines[0][i].length_ &&
                cross_points[j].y_ == lines[0][i].start_.y_
            ) {
                path0 -= cross_points[j].x_ - lines[0][i].start_.x_;
                break;
            } else if (
                lines[0][i].dir_ == 'U' &&
                cross_points[j].x_ == lines[0][i].start_.x_ &&
                cross_points[j].y_ >= lines[0][i].start_.y_ &&
                cross_points[j].y_ <= lines[0][i].start_.y_ + lines[0][i].length_
            ) {
                path0 += cross_points[j].y_ - lines[0][i].start_.y_;
                break;
            } else if (
                lines[0][i].dir_ == 'D' &&
                cross_points[j].x_ == lines[0][i].start_.x_ &&
                cross_points[j].y_ <= lines[0][i].start_.y_ &&
                cross_points[j].y_ >= lines[0][i].start_.y_ - lines[0][i].length_
            ) {
                path0 -= cross_points[j].y_ - lines[0][i].start_.y_;
                break;
            } else {
                path0 += lines[0][i].length_;
            }
                   
        }

        int path1 = 0;
        for (int i = 0; i < lines[1].size(); ++i) {
            if (
                lines[1][i].dir_ == 'R' &&
                cross_points[j].x_ >= lines[1][i].start_.x_ &&
                cross_points[j].x_ <= lines[1][i].start_.x_ + lines[1][i].length_ &&
                cross_points[j].y_ == lines[1][i].start_.y_
            ) {
                path1 += cross_points[j].x_ - lines[1][i].start_.x_;
                break;
            } else if (
                lines[1][i].dir_ == 'L' &&
                cross_points[j].x_ <= lines[1][i].start_.x_ &&
                cross_points[j].x_ >= lines[1][i].start_.x_ - lines[1][i].length_ &&
                cross_points[j].y_ == lines[1][i].start_.y_
            ) {
                path1 -= cross_points[j].x_ - lines[1][i].start_.x_;
                break;
            } else if (
                lines[1][i].dir_ == 'U' &&
                cross_points[j].x_ == lines[1][i].start_.x_ &&
                cross_points[j].y_ >= lines[1][i].start_.y_ &&
                cross_points[j].y_ <= lines[1][i].start_.y_ + lines[1][i].length_
            ) {
                path1 += cross_points[j].y_ - lines[1][i].start_.y_;
                break;
            } else if (
                lines[1][i].dir_ == 'D' &&
                cross_points[j].x_ == lines[1][i].start_.x_ &&
                cross_points[j].y_ <= lines[1][i].start_.y_ &&
                cross_points[j].y_ >= lines[1][i].start_.y_ - lines[1][i].length_
            ) {
                path1 -= cross_points[j].y_ - lines[1][i].start_.y_;
                break;
            } else {
                path1 += lines[1][i].length_;
            }
        }
        int sum = path0 + path1;
        if (sum < best_sum) {
            best_sum = sum;
        }
    }

    std::cout << best_sum << "\n";

    // for (int i = 0; i < 2; i++) {
    //     for (Line l : lines[i])
    //         std::cout << "P("<<l.start_.x_<<"|"<<l.start_.y_<<"), "<<l.dir_<<", "<<l.length_<<"\n";
    //     std::cout << "\n\n";
    // }
    
}