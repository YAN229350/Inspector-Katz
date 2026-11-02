#define _CRT_SECURE_NO_WARNINGS   // remove os avisos do scanf

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

void voltar(int* op) {
    printf("\n\nOpção 1 (Voltar)");
    printf("\n\nOpção: ");
    scanf("%d", op);
}

int main() {
    // Define entrada e saída de caracteres especiais
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    // Nome do PC
    char nome_pc[256];
    DWORD tamanho = sizeof(nome_pc);

    // Memória RAM
    MEMORYSTATUSEX memoria;
    memoria.dwLength = sizeof(memoria);

    // Variáveis
    int opcao[2] = { 0 };

	HKEY Chave_windows;
	char nome_windows[256];
	DWORD tamanho_nome_windows = sizeof(nome_windows);
    DWORD tipo;
    do {
        tamanho = sizeof(nome_pc);

        system("cls");

        printf("\n██╗   ██╗             ██╗                    ██████╗██╗     ██╗  ██████╗██████╗  ████████╗  ██████╗██████████╗  ████╗  ██████╗");
        printf("\n██║ ██╔═╝  ██████╗  ██████╗  ████████╗       ╚═██╔═╝████╗   ██║██╔═════╝██╔═══██╗██╔═════╝██╔═════╝╚═══██╔═══╝██╔═══██╗██╔═══██╗");
        printf("\n████╔═╝  ██╔═══██║  ╚═██╔═╝  ╚═══██╔═╝         ██║  ██╔═██╗ ██║╚═████╗  ██████╔═╝██████╗  ██║          ██║    ██║   ██║██████╔═╝");
        printf("\n██╔═██╗  ██║   ██║    ██║      ██╔═╝           ██║  ██║ ╚═████║  ╚═══██╗██╔═══╝  ██╔═══╝  ██║          ██║    ██║   ██║██╔═██║  ");
        printf("\n██║ ╚═██╗╚═████████╗  ╚═████╗████████╗       ██████╗██║   ╚═██║██████╔═╝██║      ████████╗╚═██████╗    ██║    ╚═████╔═╝██║ ╚═██╗");
        printf("\n╚═╝   ╚═╝  ╚═══════╝    ╚═══╝╚═══════╝       ╚═════╝╚═╝     ╚═╝╚═════╝  ╚═╝      ╚═══════╝  ╚═════╝    ╚═╝      ╚═══╝  ╚═╝");

        printf("\n\nOpção 1 (Informações Básicas do Sistema Operacional)");
        printf("\nOpção 2 (Sobre RAM)");
        printf("\nOpção 3 (Sobre o Processador)");
        printf("\nOpção 4 (Créditos)");
        printf("\nOpção 5 (Sair)");

        printf("\n\nOpção: ");
        scanf("%d", &opcao[0]);

        system("cls");

        printf("\n██╗   ██╗             ██╗                    ██████╗██╗     ██╗  ██████╗██████╗  ████████╗  ██████╗██████████╗  ████╗  ██████╗");
        printf("\n██║ ██╔═╝  ██████╗  ██████╗  ████████╗       ╚═██╔═╝████╗   ██║██╔═════╝██╔═══██╗██╔═════╝██╔═════╝╚═══██╔═══╝██╔═══██╗██╔═══██╗");
        printf("\n████╔═╝  ██╔═══██║  ╚═██╔═╝  ╚═══██╔═╝         ██║  ██╔═██╗ ██║╚═████╗  ██████╔═╝██████╗  ██║          ██║    ██║   ██║██████╔═╝");
        printf("\n██╔═██╗  ██║   ██║    ██║      ██╔═╝           ██║  ██║ ╚═████║  ╚═══██╗██╔═══╝  ██╔═══╝  ██║          ██║    ██║   ██║██╔═██║  ");
        printf("\n██║ ╚═██╗╚═████████╗  ╚═████╗████████╗       ██████╗██║   ╚═██║██████╔═╝██║      ████████╗╚═██████╗    ██║    ╚═████╔═╝██║ ╚═██╗");
        printf("\n╚═╝   ╚═╝  ╚═══════╝    ╚═══╝╚═══════╝       ╚═════╝╚═╝     ╚═╝╚═════╝  ╚═╝      ╚═══════╝  ╚═════╝    ╚═╝      ╚═══╝  ╚═╝");

        switch (opcao[0]) {

            // Informações básicas do sistema
        case 1: {
            if (GetComputerNameA(nome_pc, &tamanho)) {
                printf("\nNome do Desktop: %s", nome_pc);
            }
            else {
                DWORD erro = GetLastError();
                printf("Erro: não foi possível encontrar o nome do computador!");
                printf("\n\nErro: %lu", erro);
            }

            voltar(&opcao[1]);
            break;
        }

              // Informações da RAM
        case 2:
            if (GlobalMemoryStatusEx(&memoria)) {
                double ram_total =
                    (double)memoria.ullTotalPhys / (1024.0 * 1024.0 * 1024.0);

                double ram_disponivel =
                    (double)memoria.ullAvailPhys / (1024.0 * 1024.0 * 1024.0);

                double ram_uso_porcentagem =
                    (double)memoria.dwMemoryLoad;

                double ram_uso_GIB =
                    ram_total - ram_disponivel;

                printf("\n(Inspetor de RAM)");
                printf("\n\nTotal de memória física: %.2f GiB", ram_total);
                printf("\nRAM disponível: %.2f GiB", ram_disponivel);
                printf("\nUso da RAM: %.0f%%", ram_uso_porcentagem);
                printf("\nUso da RAM em GiB: %.1f GiB", ram_uso_GIB);

                voltar(&opcao[1]);
            }
            else {
                DWORD erro = GetLastError();

                printf("Erro: não foi possível detectar sua memória RAM");
                printf("\n\nERRO: %lu", erro);

                voltar(&opcao[1]);
            }
            break;

            // Processador - ainda não implementado
        case 3:
            printf("\nInformações do processador ainda não implementadas.");
            voltar(&opcao[1]);
            break;

            // Créditos
        case 4:
            printf("\nFeito por: Katz");
            voltar(&opcao[1]);
            break;

            // Sair
        case 5:
            return 0;

        default:
            printf("\nOpção inválida");
            voltar(&opcao[1]);
        }

    } while (opcao[1] == 1);

    return 0;
}