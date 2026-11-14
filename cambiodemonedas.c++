#include <iostream>
#include <vector>
#include <sstream>
#include <string>
using namespace std;
int main() {
    string linea;
    cout << "Ingrese las denominaciones de monedas separadas por espacio: ";
    getline(cin, linea);
    stringstream ss(linea);
    vector<int> monedas;
    int valor;
    while (ss >> valor) {
        if (valor > 0) {
            monedas.push_back(valor);
        }
    }
    if (monedas.empty()) {
        cout << "Debe ingresar al menos una denominacion valida." << endl;
        return 1;
    }
    int objetivo;
    cout << "Ingrese la cantidad objetivo: ";
    if (!(cin >> objetivo) || objetivo < 0) {
        cout << "La cantidad objetivo debe ser un entero no negativo." << endl;
        return 1;
    }
    int infinito = objetivo + 1;
    vector<int> dp(objetivo + 1, infinito);
    vector<int> ultimaMoneda(objetivo + 1, -1);
    dp[0] = 0;
    for (int i = 1; i <= objetivo; i++) {
        for (int moneda : monedas) {
            if (i - moneda >= 0 && dp[i - moneda] + 1 < dp[i]) {
                dp[i] = dp[i - moneda] + 1;
                ultimaMoneda[i] = moneda;
            }
        }
    }
    if (dp[objetivo] > objetivo) {
        cout << "No es posible formar la cantidad objetivo con las monedas dadas." << endl;
    } else {
        cout << "Cantidad minima de monedas: " << dp[objetivo] << endl;
        vector<int> combinacion;
        int actual = objetivo;
        while (actual > 0) {
            int m = ultimaMoneda[actual];
            combinacion.push_back(m);
            actual -= m;
        }
        cout << "Combinacion: ";
        for (size_t i = 0; i < combinacion.size(); i++) {
            cout << combinacion[i] << (i + 1 < combinacion.size() ? "+" : "");
        }
        cout << endl;
        cout << "Tabla DP:" << endl;
        cout << "[";
        for (int i = 0; i <= objetivo; i++) {
            cout << dp[i] << (i < objetivo ? ", " : "");
        }
        cout << "]" << endl;
    }
    return 0;
}
