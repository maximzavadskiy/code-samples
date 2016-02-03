@S = window.S ? {}

class S.RealtimePositioningApplication
	constructor: (@mapTag)  ->
		@map = L.map(@mapTag).setView([60.178479, 24.794231], 17)
		#floor plan
		#onMapClick = (e) ->
		L.tileLayer("http://{s}.tile.osm.org/{z}/{x}/{y}.png",
				maxZoom: 22, attribution: "Map data &copy; <a href=\"http://openstreetmap.org\">OpenStreetMap</a> contributors, <a href=\"http://creativecommons.org/licenses/by-sa/2.0/\">CC-BY-SA</a>, Imagery © <a href=\"http://cloudmade.com\">CloudMade</a>"
		).addTo @map
		LDebug.initialize @map
		@initFloorPlanModule()

	showFloor: (floorNo) ->
		@buildingPlan.setCurrentFloorIndex floorNo

	# watches tags from json info that it gets from url provided
	watchTags: (urlPrefix) ->
		requestPeriod = 500

		failHandler = (jqXHR, textStatus, errorThrown) ->
			console.log ("### error: ")
			console.log textStatus
			console.log errorThrown
			console.log "#########"

		updateTagsInfo= => ##while we are running the app
			request = $.get "#{urlPrefix}all", @processTagList, "text" #to force not to parse by jQuery
			request.fail failHandler
			setTimeout updateTagsInfo, requestPeriod

		updateTagsPosition= =>
			#console.log "updateTagsPosition"
			tagRequest = ""
			tagRequest += "tag=#{locationTag.getTagId()}&"  for locationTag in @locationTags
			tagRequest = tagRequest.slice 0, -1 #remove last &

			request = $.get "#{urlPrefix}find", "#{tagRequest}", @processTagsPosition, "text" #to force not to parse by jQuery

			request.fail failHandler



			$(".tagList").html ""
			for tag in @locationTags
				date = new Date tag.getUpdateTimestamp()

				tagListItem = document.createElement('a')
				$(tagListItem).html ( " <b> <a href='#' class='tagAnchor'>#{tag.getTagId()} </a> </b> . Last update: #{@timeSince date} <br>")

				$(tagListItem).find(".tagAnchor").click  (e) =>
					@buildingPlan.openTagPopupById parseInt $(e.target).html().trim()

				$(".tagList").append tagListItem

			setTimeout updateTagsPosition, requestPeriod

		updateTagsInfo()
		updateTagsPosition()

	processTagList : (data, status) =>
			# fix for Chrome, somehow data is alerady parsed json, TODO make it unified
		unless typeof data is  "string"
			console.log "response is not a string"   #object -> convert to string
			data = JSON.stringify data

		#console.log "Tags active: " + data
		currentTags= $.parseJSON(data).tags
		#console.log "Tags active (parsed): " + currentTags

		#TODO optimize in one loop
		#add new tags
		for newTagId in currentTags
			if jQuery.inArray(newTagId, @tagIds) is -1
				@tagIds.push newTagId

				newLocationTag = new S.TagLocation newTagId
				@locationTags.push newLocationTag
				@buildingPlan.addMarker newLocationTag

				console.log "new tag added: #{newTagId}"


		#remove old tags
		for oldTagId in @tagIds
			if jQuery.inArray(oldTagId, currentTags) is -1 # not active anymore
				console.log "tag  #{oldTagId} is not active anymore"

				oldMarkerArr = jQuery.grep @locationTags, (locationTag) ->
					return locationTag.getTagId() is oldTagId

				#remove it from cache arrays
				@locationTags = jQuery.grep @locationTags, (locationTag) ->
					return locationTag != oldMarkerArr[0]

				@tagIds = jQuery.grep @tagIds, (tagId) ->
					return tagId != oldTagId

				#remove it from the plan
				@buildingPlan.removeMarker oldMarkerArr[0]

		# $(".tagList").html JSON.stringify JSON.parse(data).tags

		## todo might execute before we get the previous data

	processTagsPosition: (data, status) =>
		#console.log "request successfull!"
		#cannot user locationTag here as it will be changed in nex for cycle to the last tag id

		unless typeof data is  "string"
			console.log "response is not a string"   #object -> convert to string
			data = JSON.stringify data


		#trim extra {} TODO artem should not cause that!
		#data = data.slice(1,-1) if data[0] = '{'

		tagsPosInfo = $.parseJSON data

		for tagPosInfo in tagsPosInfo # update tag position for each tag from Json
			curLocationTag=null
			for tag in @locationTags
				if tag.getTagId() is tagPosInfo.tagID
					curLocationTag = tag

			#console.log "Posiion info for tag #{curLocationTag.getTagId()}: " + data
			curLocationTag.onTagMove new L.latLng(tagPosInfo.position.gpsCoordinates.latitude, tagPosInfo.position.gpsCoordinates.longitude), parseInt( tagPosInfo.position.floor ), tagPosInfo.timestamp
		# now we update markers, in case they were just created with latlng 0,0 TODO call only when needed
		@buildingPlan.updateMarkerVisibility()

	timeSince: (date) ->

		seconds = Math.floor((new Date() - date) / 1000);

		interval = Math.floor(seconds / 31536000);

		if (interval > 1)
			return interval + " years"

		interval = Math.floor(seconds / 2592000);
		if (interval > 1)
			return interval + " months"

		interval = Math.floor(seconds / 86400);
		if (interval > 1)
			return interval + " days"

		interval = Math.floor(seconds / 3600);
		if (interval > 1)
			return interval + " hours"

		interval = Math.floor(seconds / 60);
		if (interval > 1)
			return interval + " minutes"

		return Math.floor(seconds) + " seconds"

	initFloorPlanModule: ->
		@buildingPlan = new S.BuildingPlanLayer  new L.LatLngBounds(0, 0)
		@setBuilding 1

		@buildingPlan.addTo @map

		@buildingPlan.setCurrentFloorIndex 0

	setBuilding: (num) ->
		angle = -48
		opacity = 1
		saveScale = yes

		floor0url=""
		floor1url=""

		if num is 0
			ne = new L.LatLng(60.17919579102684, 24.795671850442883)
			sw = new L.LatLng(60.178403484619814, 24.792993664741516)

			floor0url= "res/floor1.png"
			floor1url= "res/floor2.png"

		else if num is 1
			ne = new L.LatLng(60.17919345681888, 24.795673862099648)
			sw = new L.LatLng(60.17865891882371, 24.793446958065033)

			floor0url= "res/weegee_pohjapiirros_alakerta_final.png"
			floor1url= "res/weegee_pohjapiirros_ylakerta_final.png"


		@buildingPlan.setParams  new L.LatLngBounds(sw, ne), angle, saveScale, opacity: opacity
		@buildingPlan.setFloorLayer 0,floor0url
		@buildingPlan.setFloorLayer 1, floor1url




	tagIds : []
	locationTags : []


app =  new S.RealtimePositioningApplication "map"

app.setBuilding parseInt $(".selBuildingNumber").val()
app.showFloor parseInt $(".selFloorNumber").val()

app.watchTags "[URL HIDDEN IN THIS CODE SAMPLE]"


$(".selFloorNumber").change ->
	app.showFloor parseInt $(".selFloorNumber").val()

$(".selBuildingNumber").change ->
	app.setBuilding parseInt $(".selBuildingNumber").val()
	app.showFloor parseInt $(".selFloorNumber").val()