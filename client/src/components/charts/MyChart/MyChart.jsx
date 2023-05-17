/* eslint-disable no-unused-vars */
import './MyChart.scss'
import { useState, useEffect, Fragment } from 'react';
import { LineChart, Line, XAxis, YAxis, CartesianGrid, Tooltip, Legend, Label, LabelList } from 'recharts';

const MyChart = () => {
  const [data, setData] = useState([]);

  useEffect(() => {
    const fetchData = async () => {
      const result = await fetch('https://jcolaco.dev/api/sensors');
      const json = await result.json();
      setData(filterSoil7Humidity(json));
    };
    fetchData();
  }, []);

  function filterSoil7Humidity(data) {
    return data.filter(item => item.soil7.humidity !== 0);
  }

  const renderAirHumidityTemperatureLines = () => {
    const lines = [];
    const soil7Data = data[0]?.bme_680;
    if (soil7Data) {
      lines.push(
        <Fragment key="hum">
        <Line
        key="humidity"
        type="monotone"
        dataKey="bme_680.humidity"
        stroke="#8884d8"
        yAxisId="humidity"
        dot={false}
        >
      </Line>
      <YAxis key="h_y" yAxisId="humidity" orientation="right" tickFormatter={addHumidityUnit}/>
          </Fragment>
      
      );
      lines.push(
        <Fragment key="temp">
        <Line
        key="temperature"
        type="monotone"
        dataKey="bme_680.temperature"
        stroke="#82ca9d"
        yAxisId="temperature"
        dot={false}
        >
      </Line>
        {/* <YAxis key="t_y" yAxisId="temperature" orientation="left" tickFormatter={addTemperatureUnit} /> */}
          </Fragment>
      );
      lines.push(
        <Fragment key="dewPoint">
        <Line
        key="dewPoint"
        type="monotone"
        dataKey="bme_680.dewPoint"
        stroke="#82ca9d"
        yAxisId="temperature"
        dot={false}
        >
      </Line>
        <YAxis key="t_y" yAxisId="temperature" orientation="left" tickFormatter={addTemperatureUnit} />
          </Fragment>
      );
    }
    return lines;
  };

  const renderShLines = () => {
    const lines = [];
    const shData = data[0]?.sh;
    if (shData) {
      lines.push(
        shData.map((sensor, index) => (
          <Line
            key={sensor.id}
            type="monotone"
            dataKey={`sh[${index}].humidity`}
            stroke={`#${Math.floor(Math.random() * 16777215).toString(16)}`}
          />
        ))
      );
    }
    return lines;
  };

  const renderNpkLines = () => {
    const lines = [];
    const soil7Data = data[0]?.soil7;
    if (soil7Data) {
      lines.push(
        <Line
          key="n"
          type="monotone"
          dataKey="soil7.n"
          stroke={`#${Math.floor(Math.random() * 16777215).toString(16)}`}
        />
      );
      lines.push(
        <Line
          key="p"
          type="monotone"
          dataKey="soil7.p"
          stroke={`#${Math.floor(Math.random() * 16777215).toString(16)}`}
        />
      );
      lines.push(
        <Line
          key="k"
          type="monotone"
          dataKey="soil7.k"
          stroke={`#${Math.floor(Math.random() * 16777215).toString(16)}`}
        />
      );
    }
    return lines;
  };
  
  const renderHumidityTemperatureLines = () => {
    const lines = [];
    const soil7Data = data[0]?.soil7;
    if (soil7Data) {
      lines.push(
        <Fragment key="hum">
        <Line
        key="humidity"
        type="monotone"
        dataKey="soil7.humidity"
        stroke="#8884d8"
        yAxisId="humidity"
        dot={false}
        >
      </Line>
      <YAxis key="h_y" yAxisId="humidity" orientation="right" tickFormatter={addHumidityUnit}/>
          </Fragment>
      
      );
      lines.push(
        <Fragment key="temp">
        <Line
        key="temperature"
        type="monotone"
        dataKey="soil7.temperature"
        stroke="#82ca9d"
        yAxisId="temperature"
        dot={false}
        >
      </Line>
        <YAxis key="t_y" yAxisId="temperature" orientation="left" tickFormatter={addTemperatureUnit} />
          </Fragment>
      );
    }
    return lines;
  };
  const renderEcLine = () => {
    const lines = [];
    const soil7Data = data[0]?.soil7;
    if (soil7Data) {
      lines.push(
        <Fragment key="ec">
        <Line
          key="ec"
          type="monotone"
          dataKey="soil7.ec"
          yAxisId="ec"
          stroke={`#${Math.floor(Math.random() * 16777215).toString(16)}`}
          />
          <YAxis key="ec_y" yAxisId="ec" orientation="left" tickFormatter={addEcUnit}/>
          </Fragment>
      );
    }
    return lines;
  };
  
  const renderPressureLine = () => {
    const lines = [];
    const bme_680 = data[0]?.bme_680;
    if (bme_680) {
      lines.push(
        <Fragment key="pressure">
        <Line
          key="pressure"
          type="monotone"
          dataKey="bme_680.pressure"
          yAxisId="pressure"
          stroke={`#${Math.floor(Math.random() * 16777215).toString(16)}`}
          />
          <YAxis key="pressure_y" yAxisId="pressure" orientation="left" tickFormatter={addPressureUnit}/>
          </Fragment>
      );
    }
    return lines;
  };
  
  const renderGasLine = () => {
    const lines = [];
    const bme_680 = data[0]?.bme_680;
    if (bme_680) {
      lines.push(
        <Fragment key="gas">
        <Line
          key="gas"
          type="monotone"
          dataKey="bme_680.gas"
          yAxisId="gas"
          stroke={`#${Math.floor(Math.random() * 16777215).toString(16)}`}
          />
          <YAxis key="gas_y" yAxisId="gas" orientation="left" tickFormatter={addGasUnit}/>
          </Fragment>
      );
    }
    return lines;
  };
  
  const renderPhLine = () => {
    const lines = [];
    const soil7Data = data[0]?.soil7;
    if (soil7Data) {
      lines.push(
        <Fragment key="ph">
        <Line
          key="ph"
          type="monotone"
          dataKey="soil7.ph"
          yAxisId="ph"
          stroke={`#${Math.floor(Math.random() * 16777215).toString(16)}`}
          />
          <YAxis key="ph_y" yAxisId="ph" orientation="left" tickFormatter={addPhUnit}/>
          </Fragment>
      );
    }
    return lines;
  };
  
  function getDateParts(timestamp) {
    const date = new Date(timestamp);
    const year = date.getUTCFullYear();
    const month = date.getUTCMonth() + 1; // add 1 because months start at 0
    const day = date.getUTCDate();
    const hour = date.getUTCHours();
    const minute = date.getUTCMinutes();
    return { year, month, day, hour, minute };
  }
  const formatTimestampAxis = (timestamp) => 
    `${new Date(timestamp).toLocaleTimeString([], 
        {hour: '2-digit', minute:'2-digit'})}h`;

  const addNpkUnit = (value) => 
    `${value} mg/Kg`;
  const addTemperatureUnit = (value) => 
    `${value} ºC`;
  const addHumidityUnit = (value) => 
    `${value} %`;
  const addEcUnit = (value) => 
    `${value}  mS/cm`;
  const addPressureUnit = (value) => 
    `${value}  hPa`;
  const addGasUnit = (value) => 
    `${value}  KOhm`;
  const addPhUnit = (value) => 
    `${value} PH`;

  
  return (
    <section className='MyChart'>
        <h1>AgroSense</h1>

        <h2>Soil sense</h2>
        <section className='charts'>
            <article>
                <p>
                <strong>NPK - </strong>Nitrogen, phosphorus, and potassium (NPK) are the three primary macronutrients that plants need in large quantities. Nitrogen is important for leaf growth and green color, phosphorus is important for root growth and flower formation, and potassium is important for overall plant health and disease resistance. Knowing the levels of NPK in the soil can help farmers determine the need for fertilizers and amendments.
                </p>
                <LineChart
                    width={600}
                    height={300}
                    data={data}
                    margin={{ top: 5, right: 20, bottom: 5, left: 0 }}
                    >
                    <XAxis dataKey="timestamp"
                        tickFormatter={formatTimestampAxis}
                    />
                    <YAxis tickFormatter={addNpkUnit}/>
                    <CartesianGrid stroke="#ccc" strokeDasharray="5 5" />
                    <Tooltip />
                    <Legend />
                    {renderNpkLines()}
                </LineChart>
            </article>
            <article>
                <p>
                <strong>Electric conductivity - </strong>(EC) is a measure of how well the soil conducts electricity. EC is related to the soil&#39;s ability to hold and exchange nutrients. High EC levels can indicate high salt levels, which can be harmful to plants. Low EC levels can indicate poor soil fertility. EC is often used to determine the need for fertilizers and amendments.
                <br />
                Generally, EC values between 0.8 to 2.5 mS/cm are considered ideal for most crops. However, some crops, such as tomatoes and peppers, prefer higher EC values, up to 3.5 mS/cm.
                </p>
                <LineChart
                    width={600}
                    height={300}
                    data={data}
                    margin={{ top: 5, right: 20, bottom: 5, left: 0 }}
                >
                    <XAxis dataKey="timestamp"
                        tickFormatter={formatTimestampAxis}
                    />
                    <CartesianGrid stroke="#ccc" strokeDasharray="5 5" />
                    <Tooltip />
                    <Legend />
                    {renderEcLine()}
                </LineChart>
            </article>
            <article>
                <p>
                <strong>pH - </strong>pH is a measure of how acidic or alkaline the soil is. It&#39;s important to know the pH level of the soil because it affects the availability of nutrients to plants. Most plants prefer a pH range of 6.0 to 7.0, but some plants have specific pH requirements. For example, blueberries require a pH range of 4.5 to 5.2, while alfalfa prefers a pH of 6.5 to 7.5.
                </p>
                <LineChart
                    width={600}
                    height={300}
                    data={data}
                    margin={{ top: 5, right: 20, bottom: 5, left: 0 }}
                >
                    <XAxis dataKey="timestamp"
                        tickFormatter={formatTimestampAxis}
                    />
                    <CartesianGrid stroke="#ccc" strokeDasharray="5 5" />
                    <Tooltip />
                    <Legend />
                    {renderPhLine()}
                </LineChart>
            </article>
            <article>
                <p>
                <strong>Humidity - </strong>Soil moisture content or humidity is the amount of water in the soil. It is important to know soil moisture because it affects plant growth and nutrient uptake. Water is essential for plants to absorb nutrients from the soil. Overwatering or underwatering plants can lead to poor growth and yield.
                <br />
                <strong>Temperature - </strong>Soil temperature affects plant growth and development. Different plants have different temperature requirements for germination, growth, and flowering. Soil temperature can also affect microbial activity in the soil, which can impact nutrient availability.
                <br />
                Generally, most crops grow well in soil temperatures between 10-29°C, with the ideal temperature range varying for different types of crops. Cool-season crops such as lettuce and spinach prefer cooler soil temperatures around 15-18°C, while warm-season crops such as tomatoes and peppers prefer warmer soil temperatures around 21-29°C. Humidity should be between 40% and 70% depending on crops.
                </p>
                <LineChart
                    width={600}
                    height={300}
                    data={data}
                    margin={{ top: 5, right: 10, bottom: 5, left: 10 }}
                    >
                    <XAxis dataKey="timestamp"
                        tickFormatter={formatTimestampAxis}
                    />
                    <CartesianGrid stroke="#ccc" strokeDasharray="5 5" />
                    <Tooltip />
                    <Legend />
                    {renderHumidityTemperatureLines()}
                </LineChart>
            </article>
            <article>
                <LineChart
                    width={600}
                    height={300}
                    data={data}
                    margin={{ top: 5, right: 10, bottom: 5, left: 10 }}
                    >
                    <XAxis dataKey="timestamp"
                        tickFormatter={formatTimestampAxis}
                    />
                    <CartesianGrid stroke="#ccc" strokeDasharray="5 5" />
                    <Tooltip />
                    <Legend />
                    {renderShLines()}
                </LineChart>
            </article>
        </section>
        <h2>Air sense</h2>
        <section className="charts">
        <article>
                <p>
                <strong>Humidity - </strong>Air humidity measurements are important for monitoring the moisture content in the air, which can affect both plant growth and disease development. High humidity levels can promote the growth of fungal and bacterial pathogens, while low humidity can cause dehydration and wilting in plants.
                <br />
                <strong>Temperature - </strong>Air temperature readings can be used to track changes in weather patterns and identify potential frost or heat stress risks for crops. This information can also be used to determine the appropriate planting times for different crops.
                <br />
                <strong>Dew Point - </strong>Dew point is the temperature at which water droplets begin to form on surfaces. Monitoring dew point can help to identify potential moisture-related issues, such as fungal growth or excessive moisture in the soil.
                </p>
                <LineChart
                    width={600}
                    height={300}
                    data={data}
                    margin={{ top: 5, right: 10, bottom: 5, left: 10 }}
                    >
                    <XAxis dataKey="timestamp"
                        tickFormatter={formatTimestampAxis}
                    />
                    <CartesianGrid stroke="#ccc" strokeDasharray="5 5" />
                    <Tooltip />
                    <Legend />
                    {renderAirHumidityTemperatureLines()}
                </LineChart>
            </article>
            <article>
                <p>
                <strong>Pressure - </strong>Measuring atmospheric pressure is important for monitoring weather patterns and predicting changes in climate. Pressure readings can also help to determine the appropriate timing for planting and harvesting crops.
                <br />
                Altitude measurements can be useful for tracking changes in elevation, which can affect plant growth and soil composition. This data can also be used to monitor air pollution levels at different altitudes.
                </p>
                <LineChart
                    width={600}
                    height={300}
                    data={data}
                    margin={{ top: 5, right: 20, bottom: 5, left: 0 }}
                >
                    <XAxis dataKey="timestamp"
                        tickFormatter={formatTimestampAxis}
                    />
                    <CartesianGrid stroke="#ccc" strokeDasharray="5 5" />
                    <Tooltip />
                    <Legend />
                    {renderPressureLine()}
                </LineChart>
            </article>
                        <article>
                <p>
                <strong>VOC Gas - </strong>Volatile Organic Compounds (VOCs) are organic chemicals that can have harmful effects on both plants and humans. Monitoring VOC levels can help to identify potential sources of contamination and take steps to mitigate their effects.
                </p>
                <LineChart
                    width={600}
                    height={300}
                    data={data}
                    margin={{ top: 5, right: 20, bottom: 5, left: 0 }}
                >
                    <XAxis dataKey="timestamp"
                        tickFormatter={formatTimestampAxis}
                    />
                    <CartesianGrid stroke="#ccc" strokeDasharray="5 5" />
                    <Tooltip />
                    <Legend />
                    {renderGasLine()}
                </LineChart>
            </article>
        </section>
    </section>

  );
};

export default MyChart;
