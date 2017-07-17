
frequencyOfMain = 50 -- Hz

device = {
	registers = {
		{
			name = "set",
			address = 0 
		},
		{
			name = "im_dcm_i2c_h",
			address = 1 
		},
		{
			name = "im_dcm_i2c_l",
			address = 2 
		},
		{
			name = "ovp_ih",
			address = 3 
		},
		{
			name = "ovp_il",
			address = 4 
		},
		{
			name = "htemp_ih",
			address = 5 
		},
		{
			name = "htemp_il",
			address = 6 
		},
		{
			name = "ltemp_ih",
			address = 7 
		},
		{
			name = "ltemp_il",
			address = 8 
		},
		{
			name = "ytemp_ih",
			address = 9 
		},
		{
			name = "ytemp_il",
			address = 10 
		},
		{
			name = "err_ovp_i2c_h",
			address = 11 
		},
		{
			name = "err_ovp_i2c_m",
			address = 12
		},
		{
			name = "err_ovp_i2c_l",
			address = 13
		},
		{
			name = "err_cc_i2c_h",
			address = 14
		},
		{
			name = "err_cc_i2c_m",
			address = 15
		},
		{
			name = "err_cc_i2c_l",
			address = 16
		},
		{
			name = "err_toff_i2c_h",
			address = 17
		},
		{
			name = "err_toff_i2c_m",
			address = 18
		},
		{
			name = "err_toff_i2c_l",
			address = 19
		},
		{
			name = "err_dim_i2c_h",
			address = 20
		},
		{
			name = "err_dim_i2c_m",
			address = 21
		},
		{
			name = "err_dim_i2c_l",
			address = 22
		},
		{
			name = "did_h",
			address = 23,
		},
		{
			name = "did_l",
			address = 24,
		},
		{
			name = "dim_max_h",
			address = 25
		},
		{
			name = "dim_max_l",
			address = 26
		},
		{
			name = "dim_ih",
			address = 27
		},
		{
			name = "dim_il",
			address = 28
		},
		{
			name = "degree_h",
			address = 29
		},
		{
			name = "degree_l",
			address = 30 
		},
		{
			name = "vin_max_h",
			address = 31
		},
		{
			name = "vin_max_l",
			address = 32
		},
		{
			name = "vrefh_max_h",
			address = 33
		},
		{
			name = "vrefh_max_l",
			address = 34
		},
		{
			name = "vout_h",
			address = 35
		},
		{
			name = "vout_l",
			address = 36
		},
		{
			name = "iout_h",
			address = 37
		},
		{
			name = "iout_l",
			address = 38
		},
		{
			name = "cycle_1",
			address = 39
		},
		{
			name = "cycle_2",
			address = 40
		},
		{
			name = "cycle_3",
			address = 41
		},
		{
			name = "cycle_4",
			address = 42
		},
		{
			name = "status",
			address = 43
		},
		{
			name = "status_sc",
			address = 44
		},
		{
			name = "status_cf",
			address = 45
		}
	},
	parameters  = {
		{
			name = "im_dim_i2c",
			addresses = {1,2},
			readable = true,
			writable = true
		},
		{
			name = "ovp",
			addresses = {3,4},
			size = 10,
			readable = true,
			writable = true
		},
		{
			name = "ht_temp",
			addresses = {5,6},
			readable = true,
			writable = true
		},
		{
			name = "lt_temp",
			addresses = {7,8},
			readable = true,
			writable = true
		},
		{
			name = "yt_temp",
			addresses = {9,10},
			readable = true,
			writable = true
		},
		{
			name = "error_ovp_i2c",
			addresses = {11,12,13},
			size = 20,
			readable = true,
			writable = true
		},
		{
			name = "error_cc_i2c",
			addresses = {14,15,16},
			size = 20,
			readable = true,
			writable = true
		},
		{
			name = "error_toff_i2c",
			addresses = {17,18,19},
			size = 20,
			readable = true,
			writable = true
		},
		{
			name = "error_dim_i2c",
			addresses = {20,21,22},
			size = 20,
			readable = true,
			writable = true
		},
		{
			name = "did",
			addresses = {23, 24},
			readable = true,
			writable = true
		},
		{
			name = "dim_max",
			addresses = {25, 26},
			readable = true,
			writable = true
		},
		{
			name = "dim",
			addresses = {27,28},
			readable = true,
			writable = true
		},
		{
			name = "degree",
			addresses = {29,30},
			readable = true,
			writable = false
		},
		{
			name = "vin_max",
			addresses = {31,32},
			readable = true,
			writable = false
		},
		{
			name = "vrefh_max",
			addresses = {33,34},
			readable = true,
			writable = false
		},
		{
			name = "vout",
			addresses = {35,36},
			readable = true,
			writable = false
		},
		{
			name = "iout",
			addresses = {37,38},
			readable = true,
			writable = false
		},
		{
			name = "cycle",
			addresses = {39,40,41,42},
			readable = true,
			writable = false
		},
		{
			name = "status",
			addresses = {43},
			readable = true,
			writable = false
		},
		{
			name = "status_sc",
			addresses = {44},
			readable = true,
			writable = false
		},
		{
			name = "status_cf",
			addresses = {45},
			readable = true,
			writable = false
		}
	},
	flags = {
		{
			name = "ccm",
			register = "set",
			nthbit = 1,
			on = "ccm",
			off = "dcm"
		},
		{
			name = "boost",
			register = "set",
			nthbit = 2,
			on = "boost",
			off = "buck-boost"
		},
		{
			name = "hrst",
			register = "set",
			nthbit = 3,
			on = "force_reset",
			off = "release_reset"
		},
		{
			name = "ext_feed",
			register = "set",
			nthbit = 4,
			on = "external_feedback",
			off = "internal_algorithm"
		},
		{
			name = "ac_dc",
			register = "set",
			nthbit = 5,
			on = "ac",
			off = "dc"
		},
		{
			name = "i_or_v",
			register = "set",
			nthbit = 6,
			on = "current",
			off = "voltage"
		},
		{
			name = "dim_adc",
			register = "set",
			nthbit = 7,
		},
		{
			name = "ovp_temp",
			register = "set",
			nthbit = 8,
		},
		{
			name = "start",
			register = "status",
			nthbit = 1
		},
		{
			name = "stop",
			register = "status",
			nthbit = 2
		},
		{
			name = "vin_low",
			register = "status",
			nthbit = 3
		},
		{
			name = "sw",
			register = "status",
			nthbit = 4
		},
		{
			name = "err_cc_or_err_toff",
			register = "status",
			nthbit = 5,
			on = "err_cc",
			off = "err_toff"
		},
		{
			name = "err_ovp",
			register = "status",
			nthbit = 6
		},
		{
			name = "alarm_temp",
			register = "status",
			nthbit = 7
		},
		{
			name = "error_temp",
			register = "status",
			nthbit = 8
		}
	},
	extra_parameters = {
		{
			name = "power",
			get = function()
				return getParameterValue("vout") * getParameterValue("iout");
			end
		},
		{
			name = "time",
			get = function()
				return getParameterValue("cycle") / frequencyOfMain
			end
		}

	},

	operations = {
		read = function(address)
			basic_write(address)
			return basic_read()
		end,
		write = function(address, data)
			basic_write(address, data)
		end,
		multiread = function(startAddress, size)
			basic_write(startAddress)
			return basic_read(size)
		end,
		multiwrite = function(startAddress, data)
			basic_write(startAddress, data)
		end,
		shutdown = function()
			setParameterValue("dim", 0)
		end
	}
}

interface = {
	configure_panel = {
		flags = {
			"ccm",
			"boost",
			"hrst",
			"ext_feed",
			"ac_dc",
			"i_or_v",
			"dim_adc",
			"ovp_temp"
		},
		parameters = {
			"dim",
			"ovp",
			"ht_temp",
			"lt_temp",
			"yt_temp",
			"im_dim_i2c"
		}
	},
	monitoring_panel = {
		parameters = {
			"dim",
			"did",
			"ovp",
			"ht_temp",
			"lt_temp",
			"yt_temp",
			"im_dim_i2c"
		},
		flags = {
			"hrst",
			"ext_feed",
			"ac_dc",
			"i_or_v",
			"dim_adc",
			"ovp_temp"
		},
		extra_parameters = {
			"power",
			"time"
		}
	}
}
