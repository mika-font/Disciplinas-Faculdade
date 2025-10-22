abstract class Atividade {
    protected String titulo;
    protected String descricao;
    protected String status;
    protected Date prazo;

    public Atividade(String titulo, String descricao, String status, Date prazo) {
        this.titulo = titulo;
        this.descricao = descricao;
        this.status = status;
        this.prazo = prazo;
    }
    public abstract void exibirDetalhes();
}

import java.util.Date;

public class Evento extends Atividade {
    private String local;
    private Date dataInicio;
    private Date dataFim;

    public Evento(String titulo, String descricao, String status, Date prazo, String local, Date dataInicio, Date dataFim) {
        super(titulo, descricao, status, prazo);
        this.local = local;
        this.dataInicio = dataInicio;
        this.dataFim = dataFim;
    }

    public String getLocal() {
        return local;
    }
    public Date getDataInicio() {
        return dataInicio;
    }
    public Date getDataFim() {
        return dataFim;
    }

    public void setLocal(String local) {
        this.local = local;
    }
    public void setDataInicio(Date dataInicio) {
        this.dataInicio = dataInicio;
    }
    public void setDataFim(Date dataFim) {
        this.dataFim = dataFim;
    }

    @Override
    public void exibirDetalhes() {
        System.out.println("Evento: " + titulo);
        System.out.println("Descrição: " + descricao);
        System.out.println("Status: " + status);
        System.out.println("Prazo: " + prazo);
        System.out.println("Local: " + local);
    }
}

public class Tarefa extends Atividade {
    private String membrosResponsaveis;

    public Tarefa(String titulo, String descricao, String status, Date prazo, String membrosResponsaveis) {
        super(titulo, descricao, status, prazo);
        this.membrosResponsaveis = membrosResponsaveis;
    }

    public String getMembrosResponsaveis() {
        return membrosResponsaveis;
    }
    
    public void setMembrosResponsaveis(String membrosResponsaveis) {
        this.membrosResponsaveis = membrosResponsaveis;
    }

    @Override
    public void exibirDetalhes() {
        System.out.println("Tarefa: " + titulo);
        System.out.println("Descrição: " + descricao);
        System.out.println("Status: " + status);
        System.out.println("Prazo: " + prazo);
        System.out.println("Membros Responsáveis: " + membrosResponsaveis);
    }
}