import { ConfigProvider, Flex } from "antd";
import TableComponent from "./TableComponent";

function App() {
    return (
        <ConfigProvider>
          <Flex vertical style={{ background: "#645f5f",height:"100%", justifyContent: 'center', alignItems: 'center' }}>
            <Flex vertical style={{ padding: 20, alignItems: 'center' }}>
                <span style={{fontFamily:"sans-serif", fontSize:"40px" , color:"white"}}>Dashboard de análise do sistema</span>
                <TableComponent />
            </Flex>
            </Flex>
        </ConfigProvider>
    );
}

export default App;
