import influxdb_client
from influxdb_client.client.write_api import SYNCHRONOUS


def main():
    bucket= "test_bucket"
    org   = "local"
    token = "glIyxWOad7ehvn3peRqi5FBGHyhmiHLUBTbvLXR29__DPvQOqvzs-zvpHQP1y-f5QyGF9dAzax-QqznuLJs56g=="
    url   = "http://localhost:8086"
    
    client = influxdb_client.InfluxDBClient(
        url=url,
        token=token,
        org=org
    )
    
    write_api = client.write_api(write_options=SYNCHRONOUS)
    p = influxdb_client.Point("my_measurement").tag("location", "Prague").field("temperature", 25.3)
    write_api.write(bucket=bucket, org=org, record=p)

if __name__=="__main__":
    main()
