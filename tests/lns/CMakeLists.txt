file (GLOB API_SRCS "./api/*.cpp")
file (GLOB ARITHMETIC_SRCS "./arithmetic/*.cpp")
file (GLOB LOGIC_SRCS "./logic/*.cpp")

compile_all("true" "lns" "Number Systems/fixed size/logarithmic/lns/api" "${API_SRCS}")
compile_all("true" "lns" "Number Systems/fixed size/logarithmic/lns/arithmetic" "${ARITHMETIC_SRCS}")
compile_all("true" "lns" "Number Systems/fixed size/logarithmic/lns/logic" "${LOGIC_SRCS}")
