FROM gcc:4.9
COPY HW_7 /HW_7
WORKDIR /HW_7/
RUN g++ -std=c++11 -o myapp IterativeAStar.cpp
CMD ["./myapp", "5 2 4 8 10 3 11 14 6 0 9 12 13 1 15 7"]