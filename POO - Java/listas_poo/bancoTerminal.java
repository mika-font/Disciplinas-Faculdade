package src;

import java.util.Scanner;

public class bancoTerminal {
    Scanner leitor = new Scanner(System.in);
    System.out.println("Bem-vindo ao Banco Digital!");
    System.out.println("Criando a primeira conta...");
    System.out.print("Digite o nome do titular da conta 1: ");
    String nomeTitular1 = leitor.nextLine();
    ContaBancaria conta1 = new ContaBancaria("Mika", nomeTitular1);

    System.out.println("\nCriando a segunda conta...");
    System.out.print("Digite o nome do titular da conta 2 (para transferências): ");
    String nomeTitular2 = leitor.nextLine();
    ContaBancaria conta2 = new ContaBancaria("Samu", nomeTitular2);

    System.out.println("\nContas criadas! A conta principal para operações é a de "+conta1.getTitular()+".");
    int opcao = 0;
        while(opcao != 5) {
        // Exibindo o menu
        System.out.println("\n--- MENU DE OPERAÇÕES ---");
        System.out.println("Titular: " + conta1.getTitular() + " | Conta: " + conta1.getNumeroConta());
        System.out.println("1. Depositar");
        System.out.println("2. Sacar");
        System.out.println("3. Transferir para " + conta2.getTitular());
        System.out.println("4. Consultar Saldo");
        System.out.println("5. Sair");
        System.out.print("Escolha uma opção: ");

        opcao = leitor.nextInt();
        double valor;

        switch (opcao) {
            case 1:
                System.out.print("Digite o valor para depositar: ");
                valor = leitor.nextDouble();
                conta1.depositar(valor);
                break;
            case 2:
                System.out.print("Digite o valor para sacar: ");
                valor = leitor.nextDouble();
                conta1.sacar(valor);
                break;
            case 3:
                System.out.print("Digite o valor para transferir para " + conta2.getTitular() + ": ");
                valor = leitor.nextDouble();
                conta1.transferir(conta2, valor);
                break;
            case 4:
                conta1.consultarSaldo();
                break;
            case 5:
                System.out.println("Obrigado por usar nosso banco. Até logo!");
                break;
            default:
                System.out.println("Opção inválida. Tente novamente.");
        }
    }
        leitor.close();
}