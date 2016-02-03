
#TODO implement BuldingObject superclass for this and StationMarker
@S = window.S ? {}

class S.TagLocation extends L.Marker
	constructor: (@tagId) ->
		@realLatLng = new L.LatLng 0,0
		super @realLatLng


		@setIcon new L.DivIcon html: "<b> #{@tagId} </b>", className: 'tagLocation',  iconSize: new L.Point(40, 40)
		#html: '<b> #{@tagId} </b>',

		@popupContent = document.createElement('a')
		@updatePopupContent()
		@bindPopup	@popupContent

		@on "click", ->
			#!TODO popup is crated again each time it's clicked, optimize this
			@updatePopupContent()


	updatePopupContent: ->
		#TODO fix for chrome , no such method toLocaleFormat
		lastUpdate =
			(new Date @getUpdateTimestamp()).toLocaleFormat?('%H:%M:%S %d.%m.%Y') or
			(new Date @getUpdateTimestamp()).toLocaleString()

		$(@popupContent).html " <b> Lat: </b>  #{@getLat()} <br> <b>Lng: </b>  #{@getLng()} <br> " +
							  " <b> ID: </b> <input type='text' class='id' value= '#{@getTagId()}' readonly='true'/> <br>" +
							  "<b> Floor: </b> <input type='text' class='floor' readonly='true' value= '#{@getFloorNumber()}'/> <br> " +
							  "<b> Last update: </b> <input type='text' class='lastUpdate' readonly='true' value= '#{lastUpdate}'/> <br> "


	onTagMove: (latlngPos, floorNo, timestamp) ->
		prevUpdateTime = @lastUpdateTime
		@lastUpdateTime = parseInt timestamp

		if prevUpdateTime is @lastUpdateTime or latlngPos.equals @realLatLng
			return

		console.log "Moving  tag #{@tagId} to new location at #{latlngPos} !"

		#randomize it,
#		pixPos = @_map.project(latlngPos)
#		pixPos.x += (5 - Math.random()*10)
#		pixPos.y += (5 - Math.random()*10)

		@fireEvent 'beforeMove'

		@setLatLng latlngPos
		@realLatLng = new L.LatLng latlngPos.lat, latlngPos.lng #save real latlng

		@_setFloorNumber floorNo

		@updatePopupContent()

	getTagId: ->
		@tagId

	getUpdateTimestamp: ->
		@lastUpdateTime

	#!TODO study protecting private properties
	getFloorNumber: ->
		@floorNumber

	_setFloorNumber: (num)->
		if isNaN num
			console.log "ERROR in setFlooNumber - #{num} is not a number"
			return
		@floorNumber= num

	#to get rid of JSON requirements in BuildingPlan
	getJSONObject: ->
		return null

	#overriding parent
	getRealLatLng: ->
		@realLatLng


	getLat: ->
		@getRealLatLng().lat

	getLng: ->
		@getRealLatLng().lng

	tagId: ""
	name: ""
	floorNumber: 0
	lastUpdateTime: null
	popupContent: null
	realLatLng: null # cause for looking good, we may move actual tag, e.g. in case of same location overlap