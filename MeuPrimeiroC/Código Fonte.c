#define _CRT_SECURE_NO_WARNINGS   // remove os avisos do scanf

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <winreg.h>

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

    //windows
    HKEY chave_windows = NULL;
    char nome_windows[256];
    DWORD tamanho_nome_windows = sizeof(nome_windows);
    DWORD tipo;

    char versao_windows[256];
    DWORD tamanho_versao_windows = sizeof(versao_windows);

    char build_windows[256];
    DWORD tamanho_build_windows = sizeof(build_windows);

    //processador
	HKEY chave_processador = NULL;
	char nome_processador[256];
	DWORD tamanho_nome_processador = sizeof(nome_processador);
	DWORD tipo_processador;

	DWORD tamanho_buffer = 0;
	DWORD quantidade_nucleos = 0;
    PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX buffer = NULL;
    DWORD deslocamento = 0;
    do {
        SYSTEM_INFO info_sistema;
        

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
            printf("\n(Inspetor de Informações Básicas do Sistema)");

            if (GetComputerNameA(nome_pc, &tamanho)) {
                printf("\n\nNome do Desktop: %s", nome_pc);
            }
            else {
                DWORD erro = GetLastError();
                printf("Erro: não foi possível encontrar o nome do computador!");
                printf("\n\nErro: %lu", erro);
            }

            // abre a chave do registro do Windows para obter o nome do produto
            LONG resultado = RegOpenKeyExA(
                HKEY_LOCAL_MACHINE,
                "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion",
                0,
                KEY_READ,
                &chave_windows
            );

            // Verifica se a chave foi aberta com sucesso
            if (resultado == ERROR_SUCCESS) {

                // Reinicializa o tamanho do buffer
                tamanho_nome_windows = sizeof(nome_windows);

                // Consulta o nome do produto
                LONG consulta = RegQueryValueExA(
                    chave_windows,
                    "ProductName",
                    NULL,
                    &tipo,
                    (LPBYTE)nome_windows,
                    &tamanho_nome_windows
                );
                // Reinicializa o tamanho do buffer
                tamanho_versao_windows = sizeof(versao_windows);

				// Consulta a versão do Windows
                LONG consulta_versao = RegQueryValueExA(
                    chave_windows,
                    "DisplayVersion",
                    NULL,
                    &tipo,
                    (LPBYTE)versao_windows,
                    &tamanho_versao_windows
                );

                // Reinicializa o tamanho do buffer
                tamanho_build_windows = sizeof(build_windows);

				// Consulta o número da build do Windows
                LONG consulta_build = RegQueryValueExA(
                    chave_windows,
                    "CurrentBuildNumber",
                    NULL,
                    &tipo,
                    (LPBYTE)build_windows,
                    &tamanho_build_windows
                );
				
				// Verifica se a consulta foi bem-sucedida e exibe o resultado
                if (consulta == ERROR_SUCCESS) {
                    printf("\nNome do Windows: %s", nome_windows);
                }
                else {
                    printf("\nErro ao consultar ProductName: %ld", consulta);
                }

				// Consulta a versão do Windows e exibe o resultado
                if (consulta_versao == ERROR_SUCCESS) {
                    printf("\nVersão do Windows: %s", versao_windows);
                }
                else {
                    printf("\nErro ao consultar DisplayVersion: %ld", consulta_versao);
                }

				// Consulta o número da build do Windows e exibe o resultado
				if (consulta_build == ERROR_SUCCESS) {
					printf("\nNúmero da Build do Windows: %s", build_windows);
				}
				else {
					printf("\nErro ao consultar CurrentBuildNumber: %ld", consulta_build);
				}

                // Fecha a chave após utilizá-la
                RegCloseKey(chave_windows);
            }
            else {
                printf("\nErro ao abrir a chave: %ld", resultado);
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

            // Processador
        case 3: {

            LONG resultado_processador = RegOpenKeyExA(
                HKEY_LOCAL_MACHINE,
                "HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0",
                0,
                KEY_READ,
                &chave_processador
            );

            if (resultado_processador == ERROR_SUCCESS) {
                //recialização do tamanho do buffer
                tamanho_nome_processador = sizeof(nome_processador);

                // Consulta o nome do processador
                LONG consulta_processador = RegQueryValueExA(
                    chave_processador,
                    "ProcessorNameString",
                    NULL,
                    &tipo_processador,
                    (LPBYTE)nome_processador,
                    &tamanho_nome_processador
                );
                // verifica se a consulta foi bem-sucedida e exibe o resultado
                if (consulta_processador == ERROR_SUCCESS) {
                    printf("\n(Inspetor de Processador)");
                    printf("\n\nNome do Processador: %s", nome_processador);
                }
                else {
                    printf("\nErro ao consultar ProcessorNameString: %ld", consulta_processador);
                }
                RegCloseKey(chave_processador);
            }
            else {
                printf("\nErro ao abrir a chave do processador: %ld", resultado_processador);
            }
            GetNativeSystemInfo(&info_sistema);
            if (info_sistema.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64) {
                printf("\nArquitetura: x64");
            }
            else if (info_sistema.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_INTEL) {
                printf("\nArquitetura: x86");
            }
            else if (info_sistema.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_ARM) {
                printf("\nArquitetura: ARM");
            }
            else if (info_sistema.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_ARM64) {
                printf("\nArquitetura: ARM64");
            }
            else {
                printf("\nArquitetura: Desconhecida");
            }
            DWORD Threads = info_sistema.dwNumberOfProcessors;

            printf("\nQuantidade de Threads : %lu", Threads);

			//reicialização do tamanho do buffer
            tamanho_buffer = 0;

			// Chamada inicial para obter o tamanho necessário do buffer
            BOOL consulta_tamanho = GetLogicalProcessorInformationEx(
                RelationProcessorCore,
                NULL,
                &tamanho_buffer
            );

            if (consulta_tamanho || GetLastError() != ERROR_INSUFFICIENT_BUFFER) {
                printf("\nErro ao consultar o tamanho do buffer: %lu", GetLastError());
                voltar(&opcao[1]);
                break;
            }

            buffer = malloc(tamanho_buffer);

			if (buffer == NULL) {
				printf("\nErro: não foi possível alocar memória para o buffer");
				voltar(&opcao[1]);
				break;
			}

            if (!GetLogicalProcessorInformationEx(
                RelationProcessorCore,
                buffer,
                &tamanho_buffer
            )) {
                printf("\nErro ao consultar os núcleos: %lu", GetLastError());
                free(buffer);
                buffer = NULL;
                voltar(&opcao[1]);
                break;
            }

            quantidade_nucleos = 0;
            deslocamento = 0;

            while (deslocamento < tamanho_buffer) {

                PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX registro =
                    (PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX)
                    ((BYTE*)buffer + deslocamento);

                if (registro->Relationship == RelationProcessorCore) {
                    quantidade_nucleos++;
                }

                deslocamento += registro->Size;
            }
            printf("\nQuantidade de nucleos fisicos: %lu", quantidade_nucleos);
            free(buffer);
            buffer = NULL;

		}// fim do case 3
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
