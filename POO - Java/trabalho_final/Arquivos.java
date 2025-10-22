abstract class Arquivos {
    // Métodos para manipulação de arquivos
}

public class ArquivosMembros extends Arquivos {
    public void salvarMembros(ArrayList<Membros> membros) {
        // Lógica para salvar membros em um arquivo
    }

    public ArrayList<Membros> carregarMembros() {
        // Lógica para carregar membros de um arquivo
        return new ArrayList<>();
    }
}

public class ArquivosAtividades extends Arquivos {
    public void salvarAtividades(ArrayList<Atividade> atividades) {
        // Lógica para salvar atividades em um arquivo
    }

    public ArrayList<Atividade> carregarAtividades() {
        // Lógica para carregar atividades de um arquivo
        return new ArrayList<>();
    }
}

public class ArquivosEventos extends Arquivos {
    public void salvarEventos(ArrayList<Evento> eventos) {
        // Lógica para salvar eventos em um arquivo
    }

    public ArrayList<Evento> carregarEventos() {
        // Lógica para carregar eventos de um arquivo
        return new ArrayList<>();
    }
}