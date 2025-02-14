import schema

rest_api_host = '127.0.0.1'
rest_api_port = '8000'

ipv4_schema = schema.Schema(
    [
        {
            "if_name": str,
            "ipv4add": str,
            "broadcat": str,
            "prefix": int,
            "mac_addr": str
        }
    ]
)

meminfo_schema = schema.Schema(
    {
        "memTotal": str,
        "memFree": str,
        "memAvailable": str,
        "swapTotal": str,
        "swapFree": str
    }
)

hddinfo_schema = schema.Schema(
    [
        {
            "deviceName": str,
            "model": str,
            "serial": str,
            "diskSize": str
        }
    ]
)

cpuinfo_schema = schema.Schema(

    [
        {
            "model": str,
            "coreid": str,
            "frequency": str,
            "vendor": str
        }
    ]
)


def check_body(body, json_scema):
    try:
        json_scema.validate(body)
        return True
    except schema.SchemaError as exc:
        print(exc.args)
