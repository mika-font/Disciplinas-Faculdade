import java.lang.Math;

public class Circulo {
    // Atributos da classe
    private double raio;
    private String cor;

    // Metodo construtor
    public Circulo (double raio, String cor){
        System.out.println("Criando um círculo de raio " + raio + " e cor " + cor + "...");
        this.raio = raio;
        this.cor = cor;
    }

    // Métodos de comportamento
    public double calcularArea(){
        return Math.PI * Math.pow(this.raio, 2);
    }

    public double calcularPerimetro(){
        return 2 * Math.PI * this.raio;
    }

    // Métodos de acesso (Getters)
    // Como os atributos são 'private', criamos métodos públicos para que
    // outras partes do código possam "ler" seus valores de forma controlada.
    public double getRaio() {
        return this.raio;
    }

    public String getCor() {
        return this.cor;
    }

    // --- Ponto de Entrada para Execução do Programa ---
    public static void main(String[] args) {
        // Criando nosso primeiro objeto (instância) da classe Circulo
        Circulo meuCirculoAzul = new Circulo(5.0, "azul");
        Circulo meuCirculoVermelho = new Circulo(12.0, "vermelho");

        System.out.println("\n--- Informações do Círculo Azul ---");
        // Acessando os dados através dos métodos "getters"
        System.out.println("O raio do círculo é: " + meuCirculoAzul.getRaio());
        System.out.println("A cor do círculo é: " + meuCirculoAzul.getCor());

        // Chamando os métodos do objeto
        double areaAzul = meuCirculoAzul.calcularArea();
        double perimetroAzul = meuCirculoAzul.calcularPerimetro();

        // Usando String.format para controlar as casas decimais (similar ao f-string)
        System.out.println(String.format("A área do círculo é: %.2f", areaAzul));
        System.out.println(String.format("O perímetro do círculo é: %.2f", perimetroAzul));

        System.out.println("\n--- Informações do Círculo Vermelho ---");
        System.out.println("O raio do círculo vermelho é: " + meuCirculoVermelho.getRaio());
        double areaVermelha = meuCirculoVermelho.calcularArea();
        System.out.println(String.format("A área do círculo vermelho é: %.2f", areaVermelha));
    }
}