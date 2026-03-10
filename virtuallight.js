function Light() {
    this.value = "00000000";
}

Light.prototype.setColor = function(val) {
    this.value = val;
}

Light.prototype.getColor = function() {
    return this.value;
}
