

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define MAX_VAR_NUM 20

void sop2pip(std::ifstream &infile, std::ofstream &outfile) {
    /* sop文件转换成pip文件
     * 参数infile是一个sop文件
     * 输出一个pip文件
     */

    std::string next_line;

    getline(infile, next_line);  // 第一行是Probtype, 不需要
    getline(infile, next_line);  // 第二行是"Objective:", 不需要

    // handle Objective
    std::string obj_type;
    getline(infile, next_line);
    next_line.erase(0, next_line.find_first_not_of(' '));  // 删除行首空格
    obj_type = next_line.substr(0, 3);
    if (obj_type == "max") {
        outfile << "Maximize" << std::endl;
        next_line = next_line.substr(next_line.find('=') + 1);  // 不需要等号前面的部分
        next_line.erase(0, next_line.find_first_not_of(' '));   // 删除行首空格
        outfile << next_line << std::endl;
    } else if (obj_type == "min") {
        outfile << "Minimize" << std::endl;
        next_line = next_line.substr(next_line.find('=') + 1);  // 不需要等号前面的部分
        next_line.erase(0, next_line.find_first_not_of(' '));   // 删除行首空格
        outfile << next_line << std::endl;
    } else {
        std::cerr << "invalid objective type " << obj_type << std::endl;
        exit(-1);
    }

    // handle Subjectives
    getline(infile, next_line);  // 该行是"Subject to:"
    outfile << "Subject to" << std::endl;
    getline(infile, next_line);
    int count = 1;
    while (next_line != std::string("Bounds:")) {
        next_line.erase(0, next_line.find_first_not_of(' '));       // 删除行首空格
        outfile << "c" << count << ": " << next_line << std::endl;  // 输出每一个约束条件
        getline(infile, next_line);
    }

    // handle Bounds
    // 到这里表示读取到了"Bounds:"
    outfile << "Bounds" << std::endl;
    getline(infile, next_line);
    while (next_line != std::string("Binary:") && next_line != std::string("General:") && next_line != std::string("End")) {
        next_line.erase(0, next_line.find_first_not_of(' '));  // 删除行首空格
        outfile << next_line << std::endl;                     // 删除行首空格后直接输出
        getline(infile, next_line);
    }

    // handle General
    if (next_line == std::string("General:")) {
        while (next_line != std::string("Binary:") && next_line != std::string("End")) {
            next_line.erase(0, next_line.find_first_not_of(' '));  // 删除行首空格
            outfile << next_line << std::endl;                     // 删除行首空格后直接输出
            getline(infile, next_line);
        }
        outfile << std::endl;
    }

    // handle Binary
    if (next_line == std::string("Bianry:")) {
        while (next_line != std::string("End")) {
            next_line.erase(0, next_line.find_first_not_of(' '));  // 删除行首空格
            outfile << next_line << std::endl;
            getline(infile, next_line);
        }
    }

    outfile << "End";
    std::cout << "Successfully converted sop to pip." << std::endl;
}

void sop2wbo(std::ifstream &infile, std::ofstream &outfile) {
    /* sop文件转换成wbo文件
     * 参数infile是一个sop文件
     * 输出一个wbo文件
     */

    std::cout << "Please make sure that your input file has '\n' at the last line!!" << std::endl;
    std::string line;
    std::vector<std::string> lines;
    int var_count = 0, constraint = 0, soft_count = 0, mincost = 0, maxcost = 0, sumcost = 0;
    int var_flag[MAX_VAR_NUM] = {0};
    getline(infile, line);
    while (line.size() > 0) {
        if (line.find("Probtype") == std::string::npos && line.find("Objective") == std::string::npos && line.find("Subject to") == std::string::npos && line.find("Bounds") == std::string::npos && line.find("General") == std::string::npos && line.find("Binary") == std::string::npos && line.find("End") == std::string::npos) {
            line = line.erase(0, line.find_first_not_of(" "));  // 删除行首空格
            lines.push_back(line);
            constraint++;
            if (line.find("[") != std::string::npos && line.find("]") != std::string::npos) {
                soft_count++;
                sumcost += line[1] - '0';
                if (mincost == 0) {
                    mincost = line[1] - '0';
                } else {
                    if (line[0] - '0' < mincost) {
                        mincost = line[0] - '0';
                    }
                }
                if (maxcost == 0) {
                    maxcost = line[1] - '0';
                } else {
                    if (line[0] - '0' > maxcost) {
                        maxcost = line[1] - '0';
                    }
                }
            }
            for (int i = 0; i < line.size(); i++) {
                if (line[i] == 'x') {
                    var_flag[line[i + 1] - '0'] = 1;
                    i++;
                }
            }
        }
        getline(infile, line);
    }

    for (int i = 0; i < MAX_VAR_NUM; i++) {
                if (var_flag[i] == 1)
                    var_count++;
            }

    outfile << "* "
            << "#variable=" << var_count << " #constraint=" << constraint
            << " #soft=" << soft_count << " mincost" << mincost << " maxcost" << maxcost
            << " sumcost" << sumcost << std::endl;
    for (int i = 0; i < lines.size(); i++) {
        outfile << lines[i] << std::endl;
    }

    std::cout << "Successfully converted sop to wbo." << std::endl;
}

void sop2mps(std::ifstream &infile, std::ofstream &outfile) {
    // TODO:
}

int main() {
    std::cout << "Now you can transform .sop into .pip, .wbo" << std::endl;
    std::cout << "Input file to open: ";
    std::string file_name;
    std::cin >> file_name;

    std::string file_type = file_name.substr(file_name.find_last_of('.') + 1);  // 处理输入文件, 获取文件类型信息
    if (file_type != "sop") {
        std::cerr << "Invalid file type: " << file_type << std::endl;
        std::cerr << "sop file expected." << std::endl;
        return -1;
    }
    std::string prefix = file_name.substr(0, file_name.find_last_of('.'));

    std::cout << "Now enter the target type: ";
    std::string target_type;
    std::cin >> target_type;

    std::string outpath("../output/");
    std::string suffix = "." + target_type;
    std::ofstream outfile(outpath + prefix + suffix);

    std::ifstream infile(file_name);
    if (target_type == "lp") {
    } else if (target_type == "cnf") {
    } else if (target_type == "opb") {
    } else if (target_type == "pip") {
        sop2pip(infile, outfile);
    } else if (target_type == "wbo") {
        sop2wbo(infile, outfile);
    } else if (target_type == "mps") {
        sop2mps(infile, outfile);
    } else {
        std::cerr << "invalid file type: " << target_type << std::endl;
        exit(-1);
    }

    infile.close();
    outfile.close();
    return 0;
}