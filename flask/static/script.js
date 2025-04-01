function updateDisplay(data) {
    // Update PWM LEDs
    $('#L1').val(data.L1);
    $('#L1_val').text(data.L1);
    $('#L2').val(data.L2);
    $('#L2_val').text(data.L2);
    $('#L3').val(data.L3);
    $('#L3_val').text(data.L3);

    // Update Digital LED
    $('#D13_state').text(data.D13 ? 'ON' : 'OFF');

    // Update LDR
    $('#A3_val').text(data.A3);
}

// Fetch data every second
setInterval(() => {
    $.get('/data', updateDisplay);
}, 1000);

// PWM Slider Events
$('input[type="range"]').on('input', function() {
    const key = $(this).attr('id');
    const value = $(this).val();
    $.post('/control', JSON.stringify({ key, value }));
});

// Toggle Button Event
$('#D13_toggle').click(() => {
    const current = $('#D13_state').text() === 'ON';
    $.post('/control', JSON.stringify({ key: 'D13', value: !current ? 1 : 0 }));
});
