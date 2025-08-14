import java.util.Scanner;

public class contaBancaria {
	private String numeroConta;
	private double saldo;
	private String titular;

	public contaBancaria(String numeroConta, String titular) {
		this.numeroConta = numeroConta;
		this.saldo = 0.0;
		this.titular = titular;
	}

	public void depositar(double valor) {
		if (valor > 0) {
			this.saldo += valor;
			System.out.println("DepC3sito de R$ " + valor + " realizado com sucesso.");
			consultarSaldo();
		} else {
			System.out.println("Valor de depC3sito invC!lido. Por favor, insira um valor positivo.");
		}
	}

	public void sacar(double valor) {
		if (valor <= 0) {
			System.out.println("Valor de saque invC!lido.");
		} else if (this.saldo >= valor) {
			this.saldo -= valor;
			System.out.println("Saque de R$ " + valor + " realizado com sucesso.");
			consultarSaldo();
		} else {
			System.out.println("Saque nC#o realizado. Saldo insuficiente.");
		}
	}

	public void transferir(contaBancaria contaDestino, double valor) {
		if (valor <= 0) {
			System.out.println("Valor de transferC*ncia invC!lido.");
		} else if (this.saldo >= valor) {
			this.saldo -= valor;
			contaDestino.saldo += valor;
			System.out.println("TransferC*ncia de R$ " + valor + " para " + contaDestino.titular + " realizada com sucesso.");
			System.out.println("\n--- Saldo Atualizado ---");
			System.out.print("Sua conta ("+ this.titular +"): ");
			this.consultarSaldo();
			System.out.print("Conta Destino ("+ contaDestino.titular +"): ");
			contaDestino.consultarSaldo();
		} else {
			System.out.println("TransferC*ncia nC#o realizada. Saldo insuficiente.");
		}
	}

	public String getTitular() {
		return titular;
	}

	public String getNumeroConta() {
		return numeroConta;
	}

	public void consultarSaldo() {
		System.out.printf("Saldo atual: R$ %.2f%n", this.saldo);
	}

	public static void main (String args[]) {
		Scanner leitor = new Scanner(System.in);
		System.out.println("Bem-vindo ao Banco Digital!");
		System.out.println("Criando a primeira conta...");
		System.out.print("Digite o nome do titular da conta 1: ");
		String nomeTitular1 = leitor.nextLine();
		contaBancaria conta1 = new contaBancaria("1", nomeTitular1);

		System.out.println("\nCriando a segunda conta...");
		System.out.print("Digite o nome do titular da conta 2 (para transferC*ncias): ");
		String nomeTitular2 = leitor.nextLine();
		contaBancaria conta2 = new contaBancaria("2", nomeTitular2);

		System.out.println("\nContas criadas! A conta principal para operaC'C5es C) a de "+conta1.getTitular()+".");
		int opcao = 0;
		while(opcao != 5) {
			// Exibindo o menu
			System.out.println("\n--- MENU DE OPERACCES ---");
			System.out.println("Titular: " + conta1.getTitular() + " | Conta: " + conta1.getNumeroConta());
			System.out.println("1. Depositar");
			System.out.println("2. Sacar");
			System.out.println("3. Transferir para " + conta2.getTitular());
			System.out.println("4. Consultar Saldo");
			System.out.println("5. Sair");
			System.out.print("Escolha uma opC'C#o: ");

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
				System.out.println("Obrigado por usar nosso banco. AtC) logo!");
				break;
			default:
				System.out.println("OpC'C#o invC!lida. Tente novamente.");
			}
		}
		leitor.close();
	}
}


