import { useEffect, useState } from "react";
import { Flex, Table } from "antd";
import axios from "axios";
import styled from "styled-components";

const TableWrapper = styled(Flex)`
    margin: 20px;
    padding: 20px;
    background-color: #463d3d;
    justify-content: center;
    align-items: center;
    border-radius: 8px;
    box-shadow: 0 4px 6px rgba(0, 0, 0, 0.1);
    gap: 20px;
`;

const MatrixContainer = styled(Flex)`
    align-items: center;
    justify-content: center;
    width: 70%;

    margin-top: 20px;
    padding: 15px;
    background-color: #ffffff;
    border-radius: 8px;
    box-shadow: 0 2px 4px rgba(0, 0, 0, 0.1);
    padding-bottom: 40px;
    
`;

const MatrixTitle = styled.h3`
  font-size: 18px;
  color: #333;
`;
const MatrixContent = styled(Flex)`
  align-items: center;
  justify-content: center;
  position: relative;
  padding: 10px;
  width: min-content;
  
`;

const MatrixRow = styled.div`
  display: flex;
  align-items: center;
`;

const MatrixValue = styled.span`
    text-align: center;
    height: 30px;
    width: 70px;
    font-size: 20px;
    font-family: monospace;
`;

const LeftBracket = styled.div`
    position: absolute;
    left: -10px;
    top: 0;
    bottom: 0;
    width: 10px;
    border-left: 2px solid #333;
    border-top: 2px solid #333;
    border-bottom: 2px solid #333;
    border-radius: 5px 0 0 5px;
`;

const RightBracket = styled.div`
    position: absolute;
    right: -10px;
    top: 0;
    bottom: 0;
    width: 10px;
    height: 100%;
    border-right: 2px solid #333;
    border-top: 2px solid #333;
    border-bottom: 2px solid #333;
    border-radius: 0 5px 5px 0;
`;
interface Iteracao {
    iteracao: number;
    valores: (number | string)[];
}
type Matrix = number[][];


const TableComponent = () => {
    const [data, setData] = useState([]);
    const [Ainv, setAinv] = useState<Matrix>([]);
    const [loading, setLoading] = useState(true);


    useEffect(() => {
        axios.get("http://127.0.0.1:8000/dados")
            .then((response) => {
                const { Ainv, deslocamentos, iteracoes } = response.data;
                console.log(deslocamentos)
                // Formatando os dados para exibição
                const formattedData = iteracoes.map((item: Iteracao, index: number) => ({
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
        <TableWrapper vertical>
            <MatrixContainer vertical>
                <MatrixTitle>Matriz Inversa</MatrixTitle>
                <MatrixContent vertical>
                    <LeftBracket />
                    <RightBracket />
                    {Ainv.length > 0 &&
                    Ainv.map((row: number[], rowIndex:number) => (
                        <MatrixRow key={rowIndex}>
                        {row.map((value: number, colIndex:number) => (
                            <MatrixValue key={colIndex}>
                            {value.toFixed(2)}
                            </MatrixValue>
                        ))}
                        </MatrixRow>
                    ))}
                </MatrixContent>
            </MatrixContainer>
            <Flex style={{color: "white", fontFamily: "sans-serif", fontSize:"30px"}}>Iterações</Flex>
            <Table columns={columns} dataSource={data} loading={loading} />
        </TableWrapper>
    );
};

export default TableComponent;
