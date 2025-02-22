import { useEffect, useState } from "react";
import { Table } from "antd";
import axios from "axios";
import styled from "styled-components";

const TableWrapper = styled.div`
  margin: 20px;
  padding: 20px;
  background-color: #f4f7fc;
  border-radius: 8px;
  box-shadow: 0 4px 6px rgba(0, 0, 0, 0.1);
`;

const MatrixContainer = styled.div`
  margin-top: 20px;
  padding: 15px;
  background-color: #ffffff;
  border-radius: 8px;
  box-shadow: 0 2px 4px rgba(0, 0, 0, 0.1);
`;

const MatrixTitle = styled.h3`
  font-size: 18px;
  color: #333;
`;

const TableComponent = () => {
    const [data, setData] = useState([]);
    const [Ainv, setAinv] = useState([]);
    const [loading, setLoading] = useState(true);

    useEffect(() => {
        axios.get("http://127.0.0.1:8000/dados")
            .then((response) => {
                const { Ainv, deslocamentos, iteracoes } = response.data;
                
                // Formatando os dados para exibição
                const formattedData = iteracoes.map((item, index) => ({
                    key: index,
                    iteracao: item.iteracao,
                    valores: item.valores.join(", ")
                }));

                setData(formattedData);
                setAinv(Ainv);
                setLoading(false);
                console.log("Dados carregados:", formattedData);
            })
            .catch((error) => {
                console.error("Erro ao buscar dados:", error);
                setLoading(false);
            });
    }, []);

    const columns = [
        { title: "Iteração", dataIndex: "iteracao", key: "iteracao" },
        { title: "Valores", dataIndex: "valores", key: "valores" }
    ];

    return (
        <TableWrapper>
            <h2>Iterações</h2>
            <Table columns={columns} dataSource={data} loading={loading} />
            <MatrixContainer>
                <MatrixTitle>Matriz Inversa (Ainv)</MatrixTitle>
                <pre>
                    {Ainv.length > 0 &&
                        Ainv.map((row, rowIndex) => (
                            <div key={rowIndex}>
                                {row.map((value, colIndex) => (
                                    <span key={colIndex} style={{ marginRight: "10px" }}>
                                        {value.toFixed(4)}
                                    </span>
                                ))}
                            </div>
                        ))}
                </pre>
            </MatrixContainer>
        </TableWrapper>
    );
};

export default TableComponent;
