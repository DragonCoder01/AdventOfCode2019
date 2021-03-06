#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <vector>
#include <iostream>
#include <iomanip>
#include <cmath>

#include "Computer.h"

#define SUCCESSFUL_INSTRUCTION 0
#define FAILED_INSTRUCTION -2
#define HALT_INSTRUCTION -1

int base_ptr = 0;

class Parameter {
public:
    int address;
    int mode;

    Parameter(const std::vector<int64_t>& memory, int instruction_ptr, int parameter_number, int parameter_count) {
        int opcode = memory[instruction_ptr];
        int possible = opcode / 100;

        int divider = std::pow(10, parameter_number);
        mode = (possible / divider) % 10;

        if (mode == 1) {
            address = instruction_ptr + parameter_number +1;
        } else if (mode == 2) {
            address = base_ptr + memory[instruction_ptr + parameter_number+1];
        } else if (mode == 0) {
            address = memory[instruction_ptr + parameter_number+1];
        }
    }
};

class Instruction {
private:
    bool isEnabled;
public:
    virtual int code(Computer& com, std::vector<Parameter*>& parameter) = 0;

    virtual int opcode() = 0;
    virtual int parameter_count() = 0;

    Instruction() : isEnabled(false) {}

    void enable() {
        isEnabled = true;
    }

    void disable() {
        isEnabled = false;
    }

    bool enabled() {
        return isEnabled;
    }

    int execute(Computer& com) {
        if (isEnabled) {
            if (opcode() == com.read_memory(com.instruction_ptr_) % 100) {
                // std::cout << "Opcode: " << memory[instruction_ptr] << "\n";
                // std::cout << "Baseptr: " << base_ptr << ", Instructionptr: " << com.instruction_ptr_ << ", Opcode: " << com.read_memory(com.instruction_ptr_) << "\n";
                std::vector<Parameter*> parameter;
                for (int i = 0; i < parameter_count(); ++i) {
                    parameter.push_back(new Parameter(com.get_memory(), com.instruction_ptr_, i, parameter_count()));
                }

                int ret = code(com, parameter);
                if (ret < 0) {
                    return HALT_INSTRUCTION;
                } else {
                    com.instruction_ptr_ = ret;
                    return SUCCESSFUL_INSTRUCTION;
                }
            }
        }
        return FAILED_INSTRUCTION; 
    }
};

#endif