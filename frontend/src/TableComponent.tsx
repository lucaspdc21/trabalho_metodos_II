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
    //gap: 20px;
    min-width: 50vw;
`;

const MatrixContainer = styled(Flex)`
    align-items: center;
    justify-content: center;
    width: 70%;
    margin-top: 20px;
    padding: 15px;
    background-color: #ffffff;
    border-radius: 10px;
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
    height: 100%;
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

const DeslocamentosContainer = styled(Flex)`
    align-items: center;
    justify-content: center;
    width: 70%;
    margin-top: 20px;
    padding: 15px;
    background-color: #ffffff;
    border-radius: 8px;
    box-shadow: 0 2px 4px rgba(0, 0, 0, 0.1);
    margin-bottom: 80px;
`;

const DeslocamentosTitle = styled.h3`
  font-size: 18px;
  color: #333;
`;

const DeslocamentosContent = styled(Flex)`
  align-items: center;
  justify-content: center;
  position: relative;
  padding: 10px;
  width: min-content;
`;

interface Iteracao {
    iteracao: number;
    valores: (number | string)[];
}

type Matrix = number[][];

const TableComponent = () => {
    const [dataSeidel, setDataSeidel] = useState([]);
    const [dataJacobi, setDataJacobi] = useState([]);
    const [AinvSeidel, setAinvSeidel] = useState<Matrix>([]);
    const [AinvJacobi, setAinvJacobi] = useState<Matrix>([]);
    const [deslocamentosSeidel, setDeslocamentosSeidel] = useState<number[]>([]);
    const [deslocamentosJacobi, setDeslocamentosJacobi] = useState<number[]>([]);
    const [loadingSeidel, setLoadingSeidel] = useState(true);
    const [loadingJacobi, setLoadingJacobi] = useState(true);

    useEffect(() => {
        // Requisição para Gauss-Seidel
        axios.get("http://127.0.0.1:8000/dados_seidel")
            .then((response) => {
                const { Ainv, iteracoes, deslocamentos } = response.data;
                const formattedData = iteracoes.map((item: Iteracao, index: number) => ({
                    key: index,
                    iteracao: item.iteracao,
                    valores: item.valores.join(", "),
                }));
                setDataSeidel(formattedData);
                setAinvSeidel(Ainv);
                setDeslocamentosSeidel(deslocamentos);
                setLoadingSeidel(false);
            })
            .catch((error) => {
                console.error("Erro ao buscar dados de Gauss-Seidel:", error);
                setLoadingSeidel(false);
            });

        // Requisição para Gauss-Jacobi
        axios.get("http://127.0.0.1:8000/dados_jacobi")
            .then((response) => {
                const { Ainv, iteracoes, deslocamentos } = response.data;
                const formattedData = iteracoes.map((item: Iteracao, index: number) => ({
                    key: index,
                    iteracao: item.iteracao,
                    valores: item.valores.join(", "),
                }));
                setDataJacobi(formattedData);
                setAinvJacobi(Ainv);
                setDeslocamentosJacobi(deslocamentos);
                setLoadingJacobi(false);
            })
            .catch((error) => {
                console.error("Erro ao buscar dados de Gauss-Jacobi:", error);
                setLoadingJacobi(false);
            });
    }, []);

    const columns = [
        { title: "Iteração", dataIndex: "iteracao", key: "iteracao" },
        { title: "Valores", dataIndex: "valores", key: "valores" },
    ];

    return (
        <TableWrapper vertical>
            <Flex style={{ color: "white", fontFamily: "sans-serif", fontSize: "30px" }}>
                Gauss-Seidel
            </Flex>
            {/* Seção para Gauss-Seidel */}
            <MatrixContainer vertical >
                <MatrixTitle>Matriz Inversa (Gauss-Seidel)</MatrixTitle>
                <MatrixContent vertical >
                    <LeftBracket />
                    <RightBracket />
                    {AinvSeidel.length > 0 &&
                        AinvSeidel.map((row: number[], rowIndex: number) => (
                            <MatrixRow key={rowIndex}>
                                {row.map((value: number, colIndex: number) => (
                                    <MatrixValue key={colIndex}>
                                        {value.toFixed(2)}
                                    </MatrixValue>
                                ))}
                            </MatrixRow>
                        ))}
                </MatrixContent>
            </MatrixContainer>
            <Table
                columns={columns}
                dataSource={dataSeidel}
                loading={loadingSeidel}
                style={{ minWidth: "100%",backgroundColor:"white", borderRadius:"10px", marginTop:"20px" }}
            />

            {/* Seção de Deslocamentos para Gauss-Seidel */}
            <DeslocamentosContainer vertical>
                <DeslocamentosTitle>Deslocamentos (Gauss-Seidel)</DeslocamentosTitle>
                <DeslocamentosContent>
                    {deslocamentosSeidel.length > 0 &&
                        deslocamentosSeidel.map((value: number, index: number) => (
                            <MatrixValue key={index} style={{paddingRight: "30px"}}>
                                {value.toFixed(5)}
                            </MatrixValue>
                        ))}
                </DeslocamentosContent>
            </DeslocamentosContainer>

            {/* Seção para Gauss-Jacobi */}
            <Flex style={{ color: "white", fontFamily: "sans-serif", fontSize: "30px" }}>
                Gauss-Jacobi
            </Flex>
            <MatrixContainer vertical>
                <MatrixTitle>Matriz Inversa (Gauss-Jacobi)</MatrixTitle>
                <MatrixContent vertical>
                    <LeftBracket />
                    <RightBracket />
                    {AinvJacobi.length > 0 &&
                        AinvJacobi.map((row: number[], rowIndex: number) => (
                            <MatrixRow key={rowIndex}>
                                {row.map((value: number, colIndex: number) => (
                                    <MatrixValue key={colIndex}>
                                        {value.toFixed(2)}
                                    </MatrixValue>
                                ))}
                            </MatrixRow>
                        ))}
                </MatrixContent>
            </MatrixContainer>
            <Table
                columns={columns}
                dataSource={dataJacobi}
                loading={loadingJacobi}
                style={{ minWidth: "100%",backgroundColor:"white", borderRadius:"10px", marginTop:"20px" }}
            />

            {/* Seção de Deslocamentos para Gauss-Jacobi */}
            <DeslocamentosContainer vertical>
                <DeslocamentosTitle>Deslocamentos (Gauss-Jacobi)</DeslocamentosTitle>
                <DeslocamentosContent>
                    {deslocamentosJacobi.length > 0 &&
                        deslocamentosJacobi.map((value: number, index: number) => (
                            <MatrixValue key={index} style={{paddingRight: "30px"}}>
                                {value.toFixed(5)}
                            </MatrixValue>
                        ))}
                </DeslocamentosContent>
            </DeslocamentosContainer>
        </TableWrapper>
    );
};

export default TableComponent;