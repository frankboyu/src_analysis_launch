import rcdb
import os

#query = input("Input the selection query (including the quotation marks ""): \n")
db = rcdb.RCDBProvider(os.environ.get('RCDB_CONNECTION'))

good_runs = db.select_runs("@is_src_production and @status_approved and run_config == 'FCAL_BCAL_PS_SRC_m9.conf' and beam_on_current > 55.0 and target_type=='FULL & Ready Carbon'", 90001, 90662)
#good_runs = db.select_runs("@is_primex_production", 110000, 119999)

rest_count = 0
print("List of selected runs:")
for run in good_runs:

    print(run.number)

    #rawdata_count = 0
    #rawdata_path = '/mss/halld/RunPeriod-2021-11/rawdata/Run0' + str(run.number)
    #for path in os.listdir(rawdata_path):
    #    if os.path.isfile(os.path.join(rawdata_path, path)):
    #        if path[0:10] == 'hd_rawdata':
    #            rawdata_count += 1
    #print(rawdata_count)

    rest_path = '/mss/halld/RunPeriod-2021-11/recon/ver02/REST/0' + str(run.number)
    for path in os.listdir(rest_path):
        if os.path.isfile(os.path.join(rest_path, path)):
            if path[0:9] == 'dana_rest':
                rest_count += 1

print(rest_count)