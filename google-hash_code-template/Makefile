CC := gcc
CXX := g++

BUILD_TYPE := RelWithDebInfo
CPUS := $(shell bash -c 'bc <<< "$$(grep -c ^processor /proc/cpuinfo) - 1"')

BUILD_DIR := build
OUT_DIR := output

BUILD_TARGET := $(BUILD_DIR)/main

all: do_build

$(BUILD_DIR)/CMakeCache.txt: | $(BUILD_DIR)
	@cd $(BUILD_DIR) && \
	cmake -GNinja -DUSE_SANITIZER="Address;Undefined" -DCMAKE_BUILD_TYPE=$(BUILD_TYPE) ..
#  cmake -GNinja -DCMAKE_BUILD_TYPE=$(BUILD_TYPE) ..

do_build: $(BUILD_DIR)/CMakeCache.txt
	@cd $(BUILD_DIR) && \
  cmake --build . --parallel $(CPUS)

run: run_a run_b run_c run_d run_e run_f

.PHONY: run_a
run_a: $(BUILD_TARGET) | $(OUT_DIR)
	@echo "[Problem A]"
	@./$(BUILD_DIR)/main $(OUT_DIR)/result_a.txt < input/a_an_example.in.txt

.PHONY: run_b
run_b: $(BUILD_TARGET) | $(OUT_DIR)
	@echo "[Problem B]"
	@./$(BUILD_DIR)/main $(OUT_DIR)/result_b.txt < input/b_better_start_small.in.txt

.PHONY: run_c
run_c: $(BUILD_TARGET) | $(OUT_DIR)
	@echo "[Problem C]"
	@./$(BUILD_DIR)/main $(OUT_DIR)/result_c.txt < input/c_collaboration.in.txt

.PHONY: run_d
run_d: $(BUILD_TARGET) | $(OUT_DIR)
	@echo "[Problem D]"
	@./$(BUILD_DIR)/main $(OUT_DIR)/result_d.txt < input/d_dense_schedule.in.txt

.PHONY: run_e
run_e: $(BUILD_TARGET) | $(OUT_DIR)
	@echo "[Problem E]"
	@./$(BUILD_DIR)/main $(OUT_DIR)/result_e.txt < input/e_exceptional_skills.in.txt

.PHONY: run_f
run_f: $(BUILD_TARGET) | $(OUT_DIR)
	@echo "[Problem F]"
	@./$(BUILD_DIR)/main $(OUT_DIR)/result_f.txt < input/f_find_great_mentors.in.txt

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(OUT_DIR):
	mkdir -p $(OUT_DIR)

clean:
	rm -rf $(BUILD_DIR)

.PHONY: zip
zip: $(OUT_DIR)
	zip output/source.zip src/*.hpp src/*.cpp

.PHONY: all clean do_build
