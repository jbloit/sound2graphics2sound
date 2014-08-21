{
	"patcher" : 	{
		"fileversion" : 1,
		"rect" : [ 600.0, 248.0, 640.0, 506.0 ],
		"bglocked" : 0,
		"defrect" : [ 600.0, 248.0, 640.0, 506.0 ],
		"openrect" : [ 0.0, 0.0, 0.0, 0.0 ],
		"openinpresentation" : 0,
		"default_fontsize" : 12.0,
		"default_fontface" : 0,
		"default_fontname" : "Arial",
		"gridonopen" : 0,
		"gridsize" : [ 15.0, 15.0 ],
		"gridsnaponopen" : 0,
		"toolbarvisible" : 1,
		"boxanimatetime" : 200,
		"imprint" : 0,
		"boxes" : [ 			{
				"box" : 				{
					"maxclass" : "number",
					"htextcolor" : [ 0.870588, 0.870588, 0.870588, 1.0 ],
					"bgcolor" : [ 0.866667, 0.866667, 0.866667, 1.0 ],
					"fontname" : "Arial",
					"numinlets" : 1,
					"patching_rect" : [ 284.0, 86.0, 35.0, 17.0 ],
					"id" : "obj-11",
					"minimum" : 2,
					"numoutlets" : 2,
					"fontsize" : 9.0,
					"triscale" : 0.9,
					"outlettype" : [ "int", "bang" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "ftm.mess",
					"#loadbang" : 1,
					"ftm_scope" : 1,
					"presentation_rect" : [ 252.0, 64.0, 62.0, 17.0 ],
					"#init" : "1",
					"fontname" : "Geneva",
					"text" : [ "_(aa #1 1 1)" ],
					"numinlets" : 2,
					"patching_rect" : [ 252.0, 64.0, 62.0, 17.0 ],
					"id" : "obj-12",
					"#triggerall" : 0,
					"numoutlets" : 1,
					"#untuple" : 0,
					"fontsize" : 9.0,
					"outlettype" : [ "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "change",
					"fontname" : "Arial",
					"numinlets" : 1,
					"patching_rect" : [ 460.0, 164.0, 40.0, 17.0 ],
					"id" : "obj-13",
					"numoutlets" : 3,
					"fontsize" : 9.0,
					"outlettype" : [ "", "int", "int" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "ftm.mess",
					"#loadbang" : 0,
					"ftm_scope" : 0,
					"presentation_rect" : [ 460.0, 146.0, 51.0, 17.0 ],
					"#init" : "",
					"fontname" : "Geneva",
					"text" : [ "_($1 cols)" ],
					"numinlets" : 2,
					"patching_rect" : [ 460.0, 146.0, 51.0, 17.0 ],
					"id" : "obj-14",
					"#triggerall" : 0,
					"numoutlets" : 1,
					"#untuple" : 0,
					"fontsize" : 9.0,
					"outlettype" : [ "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "0",
					"fontname" : "Arial",
					"numinlets" : 2,
					"patching_rect" : [ 234.0, 153.0, 16.0, 15.0 ],
					"id" : "obj-16",
					"numoutlets" : 1,
					"fontsize" : 9.0,
					"outlettype" : [ "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "- 1",
					"fontname" : "Arial",
					"numinlets" : 2,
					"patching_rect" : [ 284.0, 144.0, 27.0, 17.0 ],
					"id" : "obj-17",
					"numoutlets" : 1,
					"fontsize" : 9.0,
					"outlettype" : [ "int" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "ftm.mess",
					"#loadbang" : 0,
					"ftm_scope" : 0,
					"presentation_rect" : [ 73.0, 197.0, 74.0, 17.0 ],
					"#init" : "",
					"fontname" : "Geneva",
					"text" : [ "_($1 rowref 0)" ],
					"numinlets" : 2,
					"patching_rect" : [ 73.0, 197.0, 74.0, 17.0 ],
					"id" : "obj-18",
					"#triggerall" : 0,
					"numoutlets" : 1,
					"#untuple" : 0,
					"fontsize" : 9.0,
					"outlettype" : [ "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "fill 0",
					"fontname" : "Arial",
					"numinlets" : 2,
					"patching_rect" : [ 363.0, 188.0, 31.0, 15.0 ],
					"id" : "obj-19",
					"numoutlets" : 1,
					"fontsize" : 9.0,
					"outlettype" : [ "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "route clear",
					"fontname" : "Arial",
					"numinlets" : 1,
					"patching_rect" : [ 73.0, 107.0, 60.0, 17.0 ],
					"id" : "obj-20",
					"numoutlets" : 2,
					"fontsize" : 9.0,
					"outlettype" : [ "", "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "ftm.mess",
					"#loadbang" : 0,
					"ftm_scope" : 0,
					"presentation_rect" : [ 460.0, 187.0, 50.0, 17.0 ],
					"#init" : "",
					"fontname" : "Geneva",
					"text" : [ "_cols $1" ],
					"numinlets" : 2,
					"patching_rect" : [ 460.0, 187.0, 50.0, 17.0 ],
					"id" : "obj-21",
					"#triggerall" : 0,
					"numoutlets" : 1,
					"#untuple" : 0,
					"fontsize" : 9.0,
					"outlettype" : [ "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "ftm.mess",
					"#loadbang" : 0,
					"ftm_scope" : 0,
					"presentation_rect" : [ 401.0, 189.0, 50.0, 17.0 ],
					"#init" : "",
					"fontname" : "Geneva",
					"text" : [ "_rows $1" ],
					"numinlets" : 2,
					"patching_rect" : [ 401.0, 189.0, 50.0, 17.0 ],
					"id" : "obj-22",
					"#triggerall" : 0,
					"numoutlets" : 1,
					"#untuple" : 0,
					"fontsize" : 9.0,
					"outlettype" : [ "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "inlet",
					"numinlets" : 0,
					"patching_rect" : [ 323.0, 65.0, 13.0, 13.0 ],
					"id" : "obj-23",
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"comment" : ""
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "t s b",
					"fontname" : "Arial",
					"numinlets" : 1,
					"patching_rect" : [ 73.0, 145.0, 121.0, 17.0 ],
					"id" : "obj-24",
					"numoutlets" : 2,
					"fontsize" : 9.0,
					"outlettype" : [ "", "bang" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "inlet",
					"numinlets" : 0,
					"patching_rect" : [ 73.0, 67.0, 15.0, 15.0 ],
					"id" : "obj-25",
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"comment" : ""
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "ftm.mess",
					"#loadbang" : 0,
					"ftm_scope" : 0,
					"presentation_rect" : [ 73.0, 221.0, 121.0, 17.0 ],
					"#init" : "",
					"fontname" : "Geneva",
					"text" : [ "_($ringbuffer row $2 $1)" ],
					"numinlets" : 2,
					"patching_rect" : [ 73.0, 221.0, 121.0, 17.0 ],
					"id" : "obj-26",
					"#triggerall" : 0,
					"numoutlets" : 1,
					"#untuple" : 0,
					"fontsize" : 9.0,
					"outlettype" : [ "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "counter 0 0 1",
					"fontname" : "Arial",
					"numinlets" : 5,
					"patching_rect" : [ 181.0, 177.0, 111.0, 17.0 ],
					"id" : "obj-27",
					"numoutlets" : 4,
					"fontsize" : 9.0,
					"outlettype" : [ "int", "", "", "int" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "ftm.object",
					"ftm_scope" : 0,
					"presentation_rect" : [ 400.0, 217.0, 100.496101, 17.0 ],
					"scope" : 0,
					"fontname" : "Geneva",
					"numinlets" : 1,
					"patching_rect" : [ 400.0, 217.0, 100.496101, 17.0 ],
					"description" : "fmat 1 1",
					"id" : "obj-28",
					"persistence" : 0,
					"name" : "ringbuffer",
					"numoutlets" : 2,
					"fontsize" : 9.0,
					"outlettype" : [ "", "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "outlet",
					"numinlets" : 1,
					"patching_rect" : [ 73.0, 401.0, 15.0, 15.0 ],
					"id" : "obj-30",
					"numoutlets" : 0,
					"comment" : ""
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "mnm.median",
					"fontname" : "Arial",
					"numinlets" : 1,
					"patching_rect" : [ 73.0, 247.0, 63.0, 17.0 ],
					"id" : "obj-31",
					"numoutlets" : 2,
					"fontsize" : 9.0,
					"outlettype" : [ "", "" ],
					"saved_object_attributes" : 					{
						"ftm_scope" : 2
					}

				}

			}
 ],
		"lines" : [ 			{
				"patchline" : 				{
					"source" : [ "obj-13", 0 ],
					"destination" : [ "obj-21", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-14", 0 ],
					"destination" : [ "obj-13", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-20", 1 ],
					"destination" : [ "obj-14", 0 ],
					"hidden" : 0,
					"midpoints" : [ 123.5, 127.0, 469.5, 127.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-22", 0 ],
					"destination" : [ "obj-28", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-21", 0 ],
					"destination" : [ "obj-28", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-19", 0 ],
					"destination" : [ "obj-28", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-11", 0 ],
					"destination" : [ "obj-22", 0 ],
					"hidden" : 0,
					"midpoints" : [ 293.5, 105.0, 410.5, 105.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-20", 0 ],
					"destination" : [ "obj-19", 0 ],
					"hidden" : 0,
					"midpoints" : [ 82.5, 133.0, 372.5, 133.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-17", 0 ],
					"destination" : [ "obj-27", 4 ],
					"hidden" : 0,
					"midpoints" : [ 293.5, 162.0, 282.5, 162.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-11", 0 ],
					"destination" : [ "obj-17", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-23", 0 ],
					"destination" : [ "obj-11", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-12", 0 ],
					"destination" : [ "obj-11", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-16", 0 ],
					"destination" : [ "obj-27", 2 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-20", 0 ],
					"destination" : [ "obj-16", 0 ],
					"hidden" : 0,
					"midpoints" : [ 82.5, 133.0, 240.0, 133.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-27", 0 ],
					"destination" : [ "obj-26", 1 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-24", 1 ],
					"destination" : [ "obj-27", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-18", 0 ],
					"destination" : [ "obj-26", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-24", 0 ],
					"destination" : [ "obj-18", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-20", 1 ],
					"destination" : [ "obj-24", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-25", 0 ],
					"destination" : [ "obj-20", 0 ],
					"hidden" : 0,
					"midpoints" : [ 82.0, 100.0, 82.5, 100.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-26", 0 ],
					"destination" : [ "obj-31", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-31", 0 ],
					"destination" : [ "obj-30", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
 ]
	}

}
