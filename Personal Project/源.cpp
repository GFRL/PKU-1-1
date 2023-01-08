#include"gfrl.h"
using namespace std;
int main() {
	int n; std::cin >> n; 
	for (int i = 1; i <= n; i++) {
		char t = getchar();
		hp_fraction A(4, 6, 1), B(1289, 2578, 1); //A.hp_fraction_cout(); B.hp_fraction_cout();
		A.hp_fraction::hp_fraction_cin(); B.hp_fraction::hp_fraction_cin();
		(A + B).hp_fraction::hp_fraction_cout(); std::cout << std::endl;
		(A - B).hp_fraction::hp_fraction_cout(); std::cout << std::endl;
		(A * B).hp_fraction::hp_fraction_cout(); std::cout << std::endl;
		(A/ B).hp_fraction::hp_fraction_cout(); std::cout << std::endl;
		if (A > hp_fraction_0)std::cout<<1<<endl;
	}
}