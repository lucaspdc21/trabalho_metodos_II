import { ConfigProvider } from "antd";
import TableComponent from "./TableComponent";

function App() {
    return (
        <ConfigProvider>
            <div style={{ padding: 20 }}>
                <h1>Dados da API</h1>
                <TableComponent />
            </div>
        </ConfigProvider>
    );
}

export default App;
